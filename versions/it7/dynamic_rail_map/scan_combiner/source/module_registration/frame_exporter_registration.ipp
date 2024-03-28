#include "modules/frame_exporters/kitti.hpp"
#include "modules/frame_exporters/uos.hpp"

namespace drm::frame_exportation {

inline constexpr auto exporters = std::make_tuple(drm::frame_exporters::kitti{}, drm::frame_exporters::uos{});

} // namespace drm::frame_exportation
