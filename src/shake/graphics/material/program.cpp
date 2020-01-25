#include "program.hpp"

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

//----------------------------------------------------------------
void attach( const gl::ProgramId& program_id, const gl::ShaderId& shader_id )
{
    gl::attach_shader( program_id, shader_id );
}

//----------------------------------------------------------------
void link( const gl::ProgramId& program_id )
{
    // Link all attached shaders
    gl::link_program( program_id );

    // Display errors
    const auto link_status = gl::get_program_iv_link_status( program_id );
    if (!link_status)
    {
        const auto program_info_log = gl::get_program_info_log( program_id );
        CHECK_FAIL( program_info_log );
    }
}

//----------------------------------------------------------------
bool is_valid( const Program& program )
{
    // Validate linked shader program
    gl::validate_program( program.get_id() );

    // Check for errors
    const auto validate_status = gl::get_program_iv_validate_status( program.get_id() );
    if (!validate_status)
    {
        const auto program_info_log = gl::get_program_info_log( program.get_id() );
        LOG( program_info_log );
        return false;
    }
    return true;
}

} // namespace anonymous

//----------------------------------------------------------------
Program::Program()
    : m_id { gl::create_program() }
{ }

//----------------------------------------------------------------
Program::~Program()
{
    if ( is_valid( m_id ) )
    {
        gl::delete_program( m_id );
    }
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
Program make_program( const Shader& vertex_shader, const Shader& fragment_shader )
{
    auto program = Program { };
    attach( program.get_id(), vertex_shader.get_id() );
    attach( program.get_id(), fragment_shader.get_id() );
    link( program.get_id() );
    return program;
}

} // namespace graphics
} // namespace shake
