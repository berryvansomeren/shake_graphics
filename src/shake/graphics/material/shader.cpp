#include "shader.hpp"

#include "shake/core/contracts/check.hpp"
#include "shake/graphics/material/glsl_preprocessor.hpp"

namespace shake {
namespace graphics {

namespace { // anonymous

//----------------------------------------------------------------
const auto invalid_shader_id = gl::ShaderId { std::numeric_limits<gl::ShaderId::value_type>::max() };

//----------------------------------------------------------------
bool is_valid( const gl::ShaderId& id )
{
    return *id < *invalid_shader_id;
}

} // anonymous

//----------------------------------------------------------------
Shader::Shader( const gl::ShaderType type ) 
    : m_id { *gl::create_shader( type ) } 
{ }

//----------------------------------------------------------------
Shader::Shader( Shader&& other )
    : m_id { other.m_id }
{
    other.m_id = invalid_shader_id;
}

//----------------------------------------------------------------
Shader& Shader::operator=( Shader&& other )
{
    m_id = other.get_id();
    other.m_id = invalid_shader_id;
    return *this;
}

//----------------------------------------------------------------
Shader::~Shader() 
{ 
    if ( is_valid( m_id ) )
    {
        gl::delete_shader( m_id ); 
    }
}

//----------------------------------------------------------------
Shader make_shader
(
    const gl::ShaderType type,
    const std::string& source
)
{
    auto shader = Shader { type };
    auto& id = shader.get_id();

    const auto preprocessed_source = glsl_preprocessor::preprocess( source, type );

    gl::shader_source( id, preprocessed_source );
    gl::compile_shader( id );

    // Check for errors
    const auto compile_status = gl::get_shader_iv_compile_status( id );
    if (!compile_status)
    {
        const auto shader_info_log = gl::get_shader_info_log( id );
        CHECK_FAIL( shader_info_log );
    }

    return shader;
}

} // namespace graphics
} // namespace shake
