## Comments inside functions

- These comments should, whenever possible, resemble a full sentence with correct grammar and punctuation.
- They should only use inline comments like this:
```c++
// Integrate velocity to approximate spacing between timed_points.  
while (point_it != points.end()) {
```
- This means multi line comments are split up into inline comments like this:
```c++
// Before being able to sample timed_points, the changing velocity  
// needs to be taken into account.
// This means finding the distances from the inner left spline point  
// to the positions from which the timed_points where scanned.  
std::vector<double> steps;
```
- and also means that the following block comment style is not allowed inside functions.
```c++
/*
 * Before being able to sample timed_points, the changing velocity  
 * needs to be taken into account.
 * This means finding the distances from the inner left spline point  
 * to the positions from which the timed_points where scanned.  
 */
 std::vector<double> steps;
```
- These comments have to be wrapped to the column character limit

## Documentation comments for functions
- Documentation comments before functions, build on the provided doxygen integration in Clion.
- This means starting with a short and precise `@brief` description of the functionality.
- This can then be followed by an optional, more detailed, description explaining the steps the function is going through and important implementation details.
- This can be followed by an optional set of `@note`s containing extra information about how the function is meant to be used.
	- This, for example, can include assumptions that the function makes about the input data or how it behaves in certain edge cases.
- This is followed by a block of `@tparam` and `@param` comments that describe in a short sentence the meaning of each parameter in the context of the function.
- Lastly, functions with return values need a `@return` comment describing the meaning of the returned value in the context of the function.
- **Important:** all the previously described blocks need to be separated by exactly one line consisting of ` *`.
- When referring to C++ types write the name out monospaced using the `@c` format option.

- Here a basic example:
```c++
/**
 * @brief Reframes lidar scans so one frame consist of points that where scanned from within a given radius.
 *
 * This function utilizes Catmull-Rom splines to approximate the positions, rotations and velocities
 * of the lidar sensor for each point.
 * This information is then used to map each point to the destination space,
 * grouping the points into frames of points that where scanned from within the given radius.
 * Subsequently, every point in a frame is transformed back to the sensor space
 * based on the average sensor pose of all the frames points.
 *
 * @note Only points with a timestamp in @c timed_transforms and @c timed_transforms are transformed.
 * @note The Catmull-Rom splines require an extra transform and velocity data point before and after the points.
 *
 * @param timed_points                    A by timestamp ascendingly sorted range of timed points to be remapped.
 * @param timed_transforms                A by timestamp ascendingly sorted range of timed tram to destination space
 * transforms .
 * @param timed_velocities                A by timestamp ascendingly sorted range of timed velocities.
 * @param sensor_to_vehicle_space         The transform from the sensor to the vehicle space.
 * @param max_sensor_position_deviation   The maximum distance in meters between scan positions in one frame.
 * @param frames                          The remapped transforms and corresponding point range.
 *
 * @return An @c std::error_code indicating possible reasons for points being omitted.
 */
[[nodiscard]] std::error_code reframe_to_closest_scan_positions(  
    tcb::span<types::timed_point_t>& timed_points,  
    tcb::span<const types::timed_transform_t> timed_transforms,  
    tcb::span<const types::timed_velocity_t> timed_velocities,  
    const types::transform_t& sensor_to_vehicle_space,  
    double max_sensor_position_deviation,  
    std::vector<types::lidar_frame_t>& frames  
);
 ```

## Documentation for classes, structs, enums, namespaces etc.
- Documentation adheres to function rules, excluding the requirement for `@param` and `@return`.
