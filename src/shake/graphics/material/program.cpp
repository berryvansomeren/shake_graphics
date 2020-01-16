#include "shader.hpp"

#include <cassert>
#include <vector>



#include "shake/core/log.hpp"
#include "shake/core/math/math.hpp"
//#include "shake/io/file.hpp"

#include "glsl_preprocessor.hpp"

namespace shake {
namespace graphics {

namespace { // anonymous

//----------------------------------------------------------------
const auto invalid_program_id = gl::ProgramId { std::numeric_limits<gl::ProgramId::value_type>::max() };

//----------------------------------------------------------------
bool is_valid( const gl::ProgramId& id )
{
    return *id < *invalid_program_id;
}

} // namespace anonymous


//----------------------------------------------------------------
bool Program::has_uniform( const std::string& uniform_name ) const
{
    return *gl::get_uniform_location( m_id, uniform_name ) >= 0;
}

//----------------------------------------------------------------
gl::UniformLocation Program::get_uniform_location( const std::string& name ) const
{
    return gl::get_uniform_location( m_id, name );
}






//----------------------------------------------------------------
Program::Program()
    : m_id { gl::create_program() }
{ }

//----------------------------------------------------------------
Program::~Program()
{
    gl::delete_program( m_id );
}


//----------------------------------------------------------------
Program::Program( Program&& other )
    : m_id { other.m_id }
{
    other.m_id = invalid_program_id;
}

//----------------------------------------------------------------
Program& Program::operator=( Program&& other )
{
    m_id = other.get_id();
    other.m_id = invalid_program_id;
    return *this;
}

//----------------------------------------------------------------
void Program::attach( const Shader& shader )
{
    gl::attach_shader( m_id, shader.get_id() );
}

//----------------------------------------------------------------
void Program::link()
{
    // Link all attached shaders
    gl::link_program( m_id );

    // Display errors
    const auto link_status = gl::get_program_iv_link_status( m_id );
    if (!link_status)
    {
        const auto program_info_log = gl::get_program_info_log( program_id );
        CHECK_FAIL( program_info_log );
    }
}

//----------------------------------------------------------------
bool Program::is_valid()
{
    // Validate linked shader program
    gl::validate_program( m_id );

    // Check for errors
    const auto validate_status = gl::get_program_iv_validate_status( m_id );
    if (!validate_status)
    {
        const auto program_info_log = gl::get_program_info_log( program_id );
        LOG( program_info_log );
        return false;
    }
    return true;
}

//----------------------------------------------------------------
std::unique_ptr<Program> Program::create_basic(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
{
    std::unique_ptr<Program> shader { std::make_unique<Program>() };

    const auto vertex_source    = glsl_preprocessor::preprocess( vertex_shader_source,    gl::ShaderType::Vertex    );
    const auto fragment_source  = glsl_preprocessor::preprocess( fragment_shader_source,  gl::ShaderType::Fragment  );

    shader->attach( vertex_source,   gl::ShaderType::Vertex   );
    shader->attach( fragment_source, gl::ShaderType::Fragment );

    shader->link();
    return shader;
}

} // namespace graphics
} // namespace shake
