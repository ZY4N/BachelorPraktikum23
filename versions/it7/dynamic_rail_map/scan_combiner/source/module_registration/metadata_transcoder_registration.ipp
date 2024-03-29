#include "modules/metadata_transcoders/json.hpp"

namespace drm::metadata_transcoding {

inline constexpr auto transcoders = std::make_tuple(drm::metadata_transcoders::json{});

} // namespace drm::metadata_transcoding
