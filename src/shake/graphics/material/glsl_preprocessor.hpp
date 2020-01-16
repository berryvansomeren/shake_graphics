#ifndef GLSL_PREPROCESSOR_HPP
#define GLSL_PREPROCESSOR_HPP

#include <string>

#include "shake/graphics/gl/gl_enum.hpp"

namespace shake {
namespace graphics {
namespace glsl_preprocessor {

std::string preprocess( const std::string& shader_source, const gl::ShaderType shader_type );

} // namespace shader_preprocessor
} // namespace graphics
} // namespace shake

#endif // GLSL_PREPROCESSOR_HPP
