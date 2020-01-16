#ifndef SHADER_HPP
#define SHADER_HPP

#include "shake/core/macros/macro_non_copyable.hpp"
#include "shake/core/macros/macro_property.hpp"

#include "shake/graphics/gl/gl_enum.hpp"
#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/gl/gl_int.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class Shader
{
public:
    // rule of 5
    Shader( const gl::ShaderType type );
    NON_COPYABLE( Shader )
    Shader( Shader&& other );
    Shader& operator=( Shader&& other );
    ~Shader();

    void source( const std::string& source );
    void compile();

private:
    PROPERTY_R( gl::ShaderId, id )
};

} // namespace graphics
} // namespace shake

#endif // SHADER_HPP