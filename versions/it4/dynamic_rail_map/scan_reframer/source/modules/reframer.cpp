#include "modules/reframer.hpp"

#include "helpers/transform_conversion.hpp"

#include <algorithm>
#include <cmath>
#include <optional>

const char* drm::reframer_error::category::name() const noexcept {
	return "reframer";
}

std::string drm::reframer_error::category::message(int ev) const {
	switch (static_cast<codes>(ev)) {
	case codes::ok:
		return "Ok";
	case codes::not_enough_transforms:
		return "Not enough transforms were given to create a Catmull-Rom spline.";
	case codes::not_enough_velocities:
		return "Not enough velocities were given to create a Catmull-Rom spline.";
	case codes::time_ranges_not_overlapping:
		return "The time ranges of the given data points were not overlapping enough to apply the algorithm.";
	case codes::no_lidar_point_entry_point_found:
		return "Searching for the first point in the overlapping time range failed.";
	case codes::no_transform_entry_point_found:
		return "Searching for the transform right before or at the first time point failed.";
	case codes::no_velocity_entry_point_found:
		return "Searching for the velocity right before or at the first time point failed.";
	default:
		using namespace std::string_literals;
		return "unrecognized error ("s + std::to_string(ev) + ")";
	}
}

std::error_category& drm::reframer_error_category() noexcept {
	static reframer_error::category category;
	return category;
}

std::error_code drm::reframer_error::make_error_code(codes e) noexcept {
	return { static_cast<int>(e), reframer_error_category() };
}

namespace drm::reframer_internal {

// The Catmull-Rom spline requires 4 points arranged as follows:
// outer_left ------- inner_left ======== inner_right ------- outer_right
// Where outer_left and outer_right can be seen as control-points
// and the actual interpolation occurs between inner_left and inner_right.
static constexpr auto outer_left = 0, inner_left = 1, inner_right = 2, outer_right = 3;

} // namespace drm::reframer_internal

template<typename T>
[[nodiscard]] static T lerp(const T& a, const T& b, double t) {
	// This implementation should be replaced with std::lerp when move to C++20 occurs.
	return a + t * (b - a);
}

template<typename T>
double drm::reframer_internal::calculate_t(const T& p0, const T& p1) noexcept {
	// Implementation derived from
	// https://en.wikipedia.org/w/index.php?title=Centripetal_Catmull%E2%80%93Rom_spline&oldid=1178082051#Code_example_in_Unreal_C++
	static constexpr auto alpha = 0.5;
	return std::pow((p1 - p0).squaredNorm(), 0.5 * alpha);
}

template<typename T>
T drm::reframer_internal::eval_catmull_rom_spline(
	const T& p0, const T& p1, const T& p2, const T& p3, double t1, double t2, double t3, double t
) noexcept {
	// Implementation derived from
	// https://en.wikipedia.org/w/index.php?title=Centripetal_Catmull%E2%80%93Rom_spline&oldid=1178082051#Code_example_in_Unreal_C++

	// For convenience the deltas are added in here
	static constexpr auto t0 = 0.0;
	t1 += t0;
	t2 += t1;
	t3 += t2;

	// Calculate distance at point t
	t = lerp(t1, t2, t);

	// Calculate point
	const auto a1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
	const auto a2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
	const auto a3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;
	const auto b1 = (t2 - t) / (t2 - t0) * a1 + (t - t0) / (t2 - t0) * a2;
	const auto b2 = (t3 - t) / (t3 - t1) * a2 + (t - t1) / (t3 - t1) * a3;
	return (t2 - t) / (t2 - t1) * b1 + (t - t1) / (t2 - t1) * b2;
}

template<typename T>
typename tcb::span<T>::reverse_iterator drm::reframer_internal::last_value_before_or_at(
	tcb::span<T> timed_values, types::timestamp_t timestamp
) noexcept {
	return std::lower_bound(
		timed_values.rbegin(),
		timed_values.rend(),
		timestamp,
		[](const auto& value, const auto& timestamp) { return value.timestamp > timestamp; }
	);
}

template<typename T>
typename tcb::span<T>::iterator drm::reframer_internal::first_value_after_or_at(
	tcb::span<T> timed_values, types::timestamp_t timestamp
) noexcept {
	return std::lower_bound(
		timed_values.begin(),
		timed_values.end(),
		timestamp,
		[](const auto& value, const auto& timestamp) { return value.timestamp < timestamp; }
	);
}

double drm::reframer_internal::advance_and_sample_velocity(
	tcb::span<const drm::types::timed_velocity_t>::iterator& velocity_it, const drm::types::timestamp_t& timestamp
) noexcept {
	// Advance velocity window (should usually only do one iteration)
	while (velocity_it[inner_right].timestamp <= timestamp) {
		++velocity_it;
	}

	assert(velocity_it[inner_left].timestamp <= timestamp);

	const auto begin_timestamp = velocity_it[outer_left].timestamp;
	const auto end_timestamp = velocity_it[outer_right].timestamp;

	const auto t =
		(std::chrono::duration<double>(timestamp - begin_timestamp).count() /
	     std::chrono::duration<double>(end_timestamp - begin_timestamp).count());

	// Catmull-rom splines don't work in 1D, so the velocity is combined
	// with its time in seconds since outer_left to make it work.
	const auto make_2D = [&begin_timestamp](const types::timed_velocity_t& timed_velocity) -> Eigen::Vector2d {
		return { std::chrono::duration<double>(timed_velocity.timestamp - begin_timestamp).count(),
			     timed_velocity.velocity };
	};

	const auto p0 = make_2D(velocity_it[outer_left]);
	const auto p1 = make_2D(velocity_it[inner_left]);
	const auto p2 = make_2D(velocity_it[inner_right]);
	const auto p3 = make_2D(velocity_it[outer_right]);

	return eval_catmull_rom_spline(p0, p1, p2, p3, calculate_t(p0, p1), calculate_t(p1, p2), calculate_t(p2, p3), t)
		.y();
}

drm::types::lidar_frame_t drm::reframer_internal::reframe_points_to_pose(
	tcb::span<types::timed_point_t> points, const types::transform_t& pose
) noexcept {
	// Invert transforms to map back to sensor space.
	const auto sensor_to_dst_space = matrix_from(pose);
	const auto dst_to_sensor_space = sensor_to_dst_space.inverse();

	// Apply transform to all points.
	for (auto& point : points) {
		point.position = dst_to_sensor_space * point.position;
	}

	return { pose, points };
}

std::pair<std::size_t, double> drm::reframer_internal::approximate_step_sizes(
	tcb::span<const drm::types::timed_transform_t>::iterator& transform_it,
	tcb::span<const drm::types::timed_velocity_t>::iterator& velocity_it,
	tcb::span<const drm::types::timed_point_t> points,
	std::vector<double>& steps
) noexcept {
	auto curr_timestamp = transform_it[inner_left].timestamp;

	// The `velocity_it[inner_left].timestamp` is guaranteed to be to the left of the current point.
	// In this case however, `curr_timestamp` points to `transform_it[inner_left].timestamp` which is to the left of
	// the point, and thus could be to the left of `velocity_it[inner_left].timestamp`.
	while (velocity_it[inner_left].timestamp > curr_timestamp) {
		--velocity_it;
	}

	auto curr_velocity = advance_and_sample_velocity(velocity_it, curr_timestamp);

	auto total_distance = 0.0;
	auto point_it = points.begin();

	steps.clear();

	// Integrate velocity to approximate spacing between timed_points.
	while (point_it != points.end()) {

		// Distance to inner_right will be needed later, so it gets mixed in here.
		const auto past_max_point = point_it->timestamp > transform_it[inner_right].timestamp;
		const auto next_timestamp = (past_max_point ? transform_it[inner_right].timestamp : point_it->timestamp);

		const auto next_velocity = advance_and_sample_velocity(velocity_it, next_timestamp);

		// Convert time delta from nanoseconds to seconds to prevent floating point precision loss.
		const auto delta_seconds = std::chrono::duration<double>(next_timestamp - curr_timestamp);

		// Use trapezoidal rule to approximate distance between timed_points.
		total_distance += lerp(curr_velocity, next_velocity, 0.5) * delta_seconds.count();

		// Only points within interval are needed later.
		if (not past_max_point) {
			steps.push_back(total_distance);
		}

		// Reached inner_right
		if (past_max_point or point_it->timestamp == transform_it[inner_right].timestamp) {
			break;
		}

		curr_timestamp = next_timestamp;
		curr_velocity = next_velocity;
		++point_it;
	}

	return { point_it - points.begin(), total_distance };
}

std::error_code drm::reframer::reframe_to_closest_scan_positions(
	tcb::span<types::timed_point_t>& timed_points,
	tcb::span<const types::timed_transform_t> timed_transforms,
	tcb::span<const types::timed_velocity_t> timed_velocities,
	const types::transform_t& sensor_to_vehicle_space,
	const double max_sensor_position_deviation,
	std::vector<types::lidar_frame_t>& frames
) noexcept {
	using namespace reframer_internal;
	using reframer_error::make_error_code;
	using reframer_error::codes;

	// Test input invariants
	const auto ascending_timestamp = [](const auto& second, const auto& first) {
		return second.timestamp < first.timestamp;
	};

	assert(std::is_sorted(timed_points.begin(), timed_points.end(), ascending_timestamp));
	assert(std::is_sorted(timed_transforms.begin(), timed_transforms.end(), ascending_timestamp));
	assert(std::is_sorted(timed_velocities.begin(), timed_velocities.end(), ascending_timestamp));

	if (timed_points.empty()) {
		return {};
	}

	// Spline interpolation is not feasible if there are fewer than four data points.
	if (timed_transforms.size() < 4) {
		timed_points = timed_points.subspan(0, 0);
		return make_error_code(codes::not_enough_transforms);
	}

	if (timed_velocities.size() < 4) {
		timed_points = timed_points.subspan(0, 0);
		return make_error_code(codes::not_enough_velocities);
	}

	// For approximating point spacing velocity data is not just needed
	// around the first point but also the first transform.
	const auto min_velocity_ts = timed_velocities[inner_left].timestamp;
	auto min_transform_it = first_value_after_or_at(timed_transforms, min_velocity_ts);
	if (min_transform_it == timed_transforms.end()) {
		timed_points = timed_points.subspan(0, 0);
		return make_error_code(codes::no_transform_entry_point_found);
	}

	// Determine the time range within which there is sufficient data to construct the splines.
	const auto min_timestamp = std::max({ min_transform_it->timestamp, timed_points.front().timestamp });
	const auto max_timestamp = std::min({ timed_transforms[timed_transforms.size() - 1 - inner_left].timestamp,
	                                      timed_velocities[timed_velocities.size() - 1 - inner_left].timestamp,
	                                      timed_points.back().timestamp });

	// Check if the time ranges overlap enough for the algorithm to work.
	if (min_timestamp >= max_timestamp) {
		timed_points = timed_points.subspan(0, 0);
		return make_error_code(codes::time_ranges_not_overlapping);
	}

	// Now that a time range is defined,
	// the begin-iterators for all involved ranges can be determined.

	auto point_it = first_value_after_or_at(timed_points, min_timestamp);
	if (point_it == timed_points.end() or point_it->timestamp > max_timestamp) {
		timed_points = timed_points.subspan(0, 0);
		return make_error_code(codes::no_lidar_point_entry_point_found);
	}

	// Signal to caller if points where skipped.
	timed_points = timed_points.subspan(point_it - timed_points.begin());

	// Find begin iterator for transforms and velocities.
	const auto spline_begin_it_for = [&](auto& timed_values, const auto timestamp) {
		using iterator = typename std::remove_cv_t<std::remove_reference_t<decltype(timed_values)>>::iterator;
		using option = std::optional<iterator>;

		const auto reverse_inner_left_it = last_value_before_or_at(timed_values, timestamp);

		if (reverse_inner_left_it + 1 < timed_values.rend()) {
			// Correct for offset added when converting reverse iterator to base
			// and shift iterator from inner_left to outer_left.
			auto outer_left_it = reverse_inner_left_it.base() - 2;
			if (reverse_inner_left_it->timestamp <= max_timestamp and
			    outer_left_it + outer_right < timed_values.end()) {

				assert(outer_left_it[inner_left].timestamp <= timestamp);
				assert(timestamp <= outer_left_it[inner_right].timestamp);

				return option{ outer_left_it };
			}
		}

		return option{ std::nullopt };
	};

	auto transform_it_opt = spline_begin_it_for(timed_transforms, point_it->timestamp);
	if (not transform_it_opt) {
		timed_points = timed_points.subspan(0, 0);
		return make_error_code(codes::no_transform_entry_point_found);
	}
	auto transform_it = transform_it_opt.value();

	auto velocity_it_opt = spline_begin_it_for(timed_velocities, transform_it[inner_left].timestamp);
	if (not velocity_it_opt) {
		timed_points = timed_points.subspan(0, 0);
		return make_error_code(codes::no_velocity_entry_point_found);
	}
	auto velocity_it = velocity_it_opt.value();

	// Sensor poses within the given radius are merged in a rolling average pose,
	// and all associated points will be reframed to this pose later.
	auto average_sensor_pose = transform_from(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
	auto num_points_in_pose = std::size_t{};

	// Square distance to avoid repeated square-root calls later.
	const auto max_sensor_position_deviation_sq = std::pow(max_sensor_position_deviation, 2.0);

	// Create sensor_to_vehicle_space for later repeated use.
	const auto sensor_to_vehicle_space_matrix = matrix_from(sensor_to_vehicle_space);

	const auto process_frame = [&]() {
		if (num_points_in_pose != 0) {
			frames.push_back(reframe_points_to_pose(
				timed_points.subspan(point_it - num_points_in_pose - timed_points.begin(), num_points_in_pose),
				average_sensor_pose
			));
		}
	};

	const auto process_points = [&](const std::size_t num_points, auto&& next_sensor_position) {
		for (std::size_t i{}; i < num_points; ++i) {
			const auto [tram_translation, tram_rotation] = next_sensor_position();

			// Create transform from sensor to destination space.
			const auto sensor_to_dst_space = matrix_from(tram_translation, tram_rotation) *
				sensor_to_vehicle_space_matrix;

			// Transform the lidar point to the destination space.
			point_it->position = sensor_to_dst_space * point_it->position;

			// Check if the newly calculated sensor translation deviates too much
			// from the center's translation to be put in the same frame.
			const auto sensor_translation = translation_from(sensor_to_dst_space);
			const auto sensor_rotation = rotation_from(sensor_to_dst_space);

			const auto to_average_sensor_position = average_sensor_pose.translation - sensor_translation;
			const auto sensor_position_deviation_sq = to_average_sensor_position.dot(to_average_sensor_position);

			if (sensor_position_deviation_sq > max_sensor_position_deviation_sq) {
				// Reframe all points within the radius.
				process_frame();

				// Begin new rolling average.
				num_points_in_pose = 1;
				average_sensor_pose.translation = sensor_translation;
				average_sensor_pose.rotation = sensor_rotation;
			} else {
				// Advance rolling average.
				++num_points_in_pose;
				const auto new_fraction = 1.0 / static_cast<double>(num_points_in_pose);
				average_sensor_pose
					.translation = lerp(average_sensor_pose.translation, sensor_translation, new_fraction);
				average_sensor_pose.rotation = average_sensor_pose.rotation.slerp(new_fraction, sensor_rotation);
			}

			++point_it;
		}
	};

	// Before being able to sample timed_points, the changing velocity
	// needs to be taken into account.
	// This means finding the distances from the inner left spline point
	// to the positions from which the timed_points where scanned.
	std::vector<double> steps;

	// One iteration transforms all timed_points that were scanned between two transforms.
	while (point_it != timed_points.end() and point_it->timestamp <= max_timestamp) {

		// Advance transform window (should usually only do one iteration)
		while (point_it->timestamp >= transform_it[inner_right].timestamp) {
			++transform_it;
		}

		assert(point_it->timestamp >= transform_it[inner_left].timestamp);

		const auto [num_points, distance] = approximate_step_sizes(
			transform_it,
			velocity_it,
			tcb::span{ point_it, timed_points.end() },
			steps
		);
		const auto t2 = calculate_t(
			transform_it[inner_left].transform.translation,
			transform_it[inner_right].transform.translation
		);

		constexpr auto epsilon = std::numeric_limits<double>::epsilon();

		if (t2 > epsilon) {

			const auto t1 = calculate_t(
				transform_it[inner_left].transform.translation,
				transform_it[outer_left].transform.translation
			);
			const auto t3 = calculate_t(
				transform_it[outer_right].transform.translation,
				transform_it[inner_right].transform.translation
			);

			if (num_points == 0) {
				continue;
			}

			if (distance > epsilon) {
				// Tram is moving and velocity is matching.
				// -> Position spline and steps can be used
				auto distance_it = steps.begin();
				process_points(num_points, [&]() {
					const auto t = *distance_it++ / distance;
					// clang-format off
					return std::pair{
						eval_catmull_rom_spline(
							transform_it[outer_left].transform.translation,
							transform_it[inner_left].transform.translation,
							transform_it[inner_right].transform.translation,
							transform_it[outer_right].transform.translation,
							t1, t2, t3,
							t
						),
						transform_it[inner_left].transform.rotation.slerp(
						t, transform_it[inner_right].transform.rotation)
					};
					// clang-format on
				});
			} else {
				// We have conflicting data, so we just assume the tram is actually moving.
				// -> Position spline and constant velocity
				const auto step_size = 1.0 / static_cast<double>(num_points);
				auto t = 0.0;

				process_points(num_points, [&]() {
					const auto tram_translation = eval_catmull_rom_spline(
						transform_it[outer_left].transform.translation,
						transform_it[inner_left].transform.translation,
						transform_it[inner_right].transform.translation,
						transform_it[outer_right].transform.translation,
						t1,
						t2,
						t3,
						t
					);
					const auto tram_rotation = transform_it[inner_left].transform.rotation.slerp(
						t,
						transform_it[inner_right].transform.rotation
					);
					t += step_size;
					return std::pair{ tram_translation, tram_rotation };
				});
			}
		} else {
			// Tram is most likely standing still.
			// -> Single point without velocity
			process_points(num_points, [&]() {
				return std::pair{ transform_it[inner_right].transform.translation,
					              transform_it[inner_right].transform.rotation };
			});
		}
	}

	// Process last frame.
	process_frame();

	// Signal to caller that timed_points where left out.
	timed_points = timed_points.subspan(0, point_it - timed_points.begin());

	return {};
}
