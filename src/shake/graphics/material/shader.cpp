#include "shader.hpp"

#include <cassert>
#include <vector>



#include "shake/core/log.hpp"
#include "shake/core/math/math.hpp"
//#include "shake/io/file.hpp"

#include "shader_preprocessor.hpp"

namespace shake {
namespace graphics {

namespace { // anonymous

//----------------------------------------------------------------
void log_gl_shader_error( const gl::ShaderId shader_id )
{
    const auto message = gl::get_shader_info_log( shader_id );
    LOG( message );
}

//----------------------------------------------------------------
void log_gl_program_error( const gl::ProgramId program_id )
{
    const auto message = gl::get_program_info_log( program_id );
    LOG( message );
}

} // namespace anonymous




//----------------------------------------------------------------
void Shader::bind() const
{
    //CHECK_NE(m_id, gl::get_current_shader_id(), "Trying to bind a shader while it is already bound.");
    //gl::set_current_shader_id(m_id);
    gl::use_program( m_id );
}

//----------------------------------------------------------------
gl::ProgramId Shader::get_program_id() const
{
    return m_id;
}

//----------------------------------------------------------------
bool Shader::has_uniform( const std::string& uniform_name ) const
{
    return *gl::get_uniform_location( m_id, uniform_name ) >= 0;
}

//----------------------------------------------------------------
gl::UniformLocation Shader::get_uniform_location( const std::string& name ) const
{
    return gl::get_uniform_location( m_id, name );
}






//----------------------------------------------------------------
Shader::Shader()
    : m_id { gl::create_program() }
{ }

//----------------------------------------------------------------
Shader::~Shader()
{
    gl::delete_program( m_id );
}

//----------------------------------------------------------------
void Shader::attach( const std::string& source, const gl::ShaderType shader_type )
{
    const char* source_ptr { source.c_str() };
    const auto shader_id = create( shader_type );
    gl::shader_source( shader_id, source );
    gl::compile_shader( shader_id );

    // Display errors
    const auto compile_status = gl::get_shader_iv_compile_status( shader_id );
    if (!compile_status)
    {
        log_gl_shader_error( shader_id );
        CHECK_FAIL( "Shader did not compile succesfully." );
    }

    // Attach shader and free allocated memory
    gl::attach_shader( m_id, shader_id );
    gl::delete_shader( shader_id );
}

//----------------------------------------------------------------
void Shader::link()
{
    // Link all attached shaders
    gl::link_program( m_id );

    // Display errors
    const auto link_status = gl::get_program_iv_link_status( m_id );
    if (!link_status)
    {
        log_gl_program_error(m_id);
        CHECK_FAIL( "Shaders could not be linked succesfully" );
    }
}

//----------------------------------------------------------------
bool Shader::is_valid()
{
    // Validate linked shader program
    gl::validate_program( m_id );

    // Display errors
    const auto validate_status = gl::get_program_iv_validate_status( m_id );
    if (!validate_status)
    {
        log_gl_program_error( m_id );
        return false;
    }
    return true;
}

//----------------------------------------------------------------
std::unique_ptr<Shader> Shader::create_basic(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
{
    std::unique_ptr<Shader> shader { std::make_unique<Shader>() };

    const auto vertex_source    = shader_preprocessor::Preprocess( vertex_shader_source,    gl::ShaderType::Vertex    );
    const auto fragment_source  = shader_preprocessor::Preprocess( fragment_shader_source,  gl::ShaderType::Fragment  );

    shader->attach( vertex_source,   gl::ShaderType::Vertex   );
    shader->attach( fragment_source, gl::ShaderType::Fragment );

    shader->link();
    return shader;
}

//----------------------------------------------------------------
gl::ShaderId Shader::create( const gl::ShaderType& type )
{
    return gl::create_shader( type );
}
} // namespace graphics
} // namespace shake
