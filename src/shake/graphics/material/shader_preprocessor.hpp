#ifndef SHADER_PREPROCESSOR_HPP
#define SHADER_PREPROCESSOR_HPP

#include <string>

#include "shake/graphics/gl/gl_enum.hpp"

namespace shake {
namespace graphics {
namespace shader_preprocessor {

std::string Preprocess( const std::string& shader_source, const gl::ShaderType shader_type );

} // namespace shader_preprocessor
} // namespace graphics
} // namespace shake

#endif // SHADER_PREPROCESSOR_HPP
