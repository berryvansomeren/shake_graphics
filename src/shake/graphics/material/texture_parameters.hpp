#ifndef TEXTURE_PARAMETERS_HPP
#define TEXTURE_PARAMETERS_HPP

#include <string>

#include "shake/core/std/map.hpp"
#include "shake/core/macros/macro_define_mapping.hpp"

namespace shake {
namespace graphics {

DEFINE_MAPPING( graphics::gl::TextureFormat, to_texture_format, std::string,
    { "r",      graphics::gl::TextureFormat::R      },
    { "rgb",    graphics::gl::TextureFormat::RGB    },
    { "rgba",   graphics::gl::TextureFormat::RGBA   }
)

DEFINE_MAPPING( graphics::gl::Filter, to_filter, std::string,
    { "linear",     graphics::gl::Filter::Linear    },
    { "nearest",    graphics::gl::Filter::Nearest   }
)

} // namespace graphics
} // namespace shake

#endif // TEXTURE_PARAMETERS_HPP
