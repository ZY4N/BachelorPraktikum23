#include "modules/point_cloud_parsers/velodyne_lidar.hpp"

namespace drm::point_cloud_parsing {

inline constexpr auto parsers = std::make_tuple(drm::point_cloud_parsers::velodyne_lidar{});

} // namespace drm::point_cloud_parsing
