#include "shader.hpp"

#include "shake/core/contracts/check.hpp"

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
void Shader::source( const std::string& source )
{
    gl::shader_source( m_id, source );
}

//----------------------------------------------------------------
void Shader::compile()
{
    gl::compile_shader( m_id );

    // Check for errors
    const auto compile_status = gl::get_shader_iv_compile_status( m_id );
    if (!compile_status)
    {
        const auto shader_info_log = gl::get_shader_info_log( m_id );
        CHECK_FAIL( shader_info_log );
    }
}

} // namespace graphics
} // namespace shake
