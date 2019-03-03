#include "shader.hpp"

#include <cassert>
#include <vector>

#include "shake/core/log.hpp"
//#include "shake/io/file.hpp"

#include "shader_preprocessor.hpp"

namespace shake {
namespace graphics {

namespace { // anonymous

//----------------------------------------------------------------
void log_gl_shader_error(GLuint shader)
{
    GLint log_length { };
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
    std::vector<GLchar> buffer(log_length);
    glGetShaderInfoLog(shader, log_length, nullptr, buffer.data());
    const std::string message { std::begin(buffer), std::end(buffer) };
    LOG( message );
}

//----------------------------------------------------------------
void log_gl_program_error(GLuint program)
{
    GLint log_length { };
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    std::vector<GLchar> buffer(log_length);
    glGetProgramInfoLog(program, log_length, nullptr, buffer.data());
    const std::string message { std::begin(buffer), std::end(buffer) };
    LOG( message );
}

} // namespace anonymous

//----------------------------------------------------------------
Shader::Shader()
    : m_id { glCreateProgram() }
{ }

//----------------------------------------------------------------
Shader::~Shader()
{
    glDeleteProgram( m_id );
}

//----------------------------------------------------------------
void Shader::attach(const std::string& source, const ShaderType shader_type )
{
    const char* source_ptr { source.c_str() };
    GLuint shader { create( shader_type ) };
    glShaderSource( shader, 1, &source_ptr, nullptr );
    glCompileShader( shader );

    // Display errors
    GLint compile_status { };
    glGetShaderiv( shader, GL_COMPILE_STATUS, &compile_status );
    if (!compile_status)
    {
        log_gl_shader_error(shader);
        assert(false && "Shader did not compile succesfully.");
    }

    // Attach shader and free allocated memory
    glAttachShader(m_id, shader);
    glDeleteShader(shader);
}

//----------------------------------------------------------------
void Shader::link()
{
    // Link all attached shaders
    glLinkProgram(m_id);

    // Display errors
    GLint link_status { };
    glGetProgramiv(m_id, GL_LINK_STATUS, &link_status);
    if (!link_status)
    {
        log_gl_program_error(m_id);
        assert(false && "Shaders could not be linked succesfully");
    }
}

//----------------------------------------------------------------
bool Shader::is_valid()
{
    // Validate linked shader program
    glValidateProgram(m_id);

    // Display errors
    GLint validate_status { };
    glGetProgramiv(m_id, GL_VALIDATE_STATUS, &validate_status);
    if (!validate_status)
    {
        log_gl_program_error(m_id);
        return false;
    }
    return true;
}

//----------------------------------------------------------------
std::unique_ptr<Shader> Shader::create_basic(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
{
    std::unique_ptr<Shader> shader { std::make_unique<Shader>() };

    const auto vertex_source    = shader_preprocessor::Preprocess( vertex_shader_source,    ShaderType::Vertex    );
    const auto fragment_source  = shader_preprocessor::Preprocess( fragment_shader_source,  ShaderType::Fragment  );

    shader->attach( vertex_source,   ShaderType::Vertex   );
    shader->attach( fragment_source, ShaderType::Fragment );

    shader->link();
    return shader;
}

//----------------------------------------------------------------
GLuint Shader::create( const ShaderType& shader_type )
{
    GLuint shader_id = 0;

    switch (shader_type)
    {
    case ShaderType::Vertex:                shader_id = glCreateShader(GL_VERTEX_SHADER);           break;
    case ShaderType::Fragment:              shader_id = glCreateShader(GL_FRAGMENT_SHADER);         break;
    case ShaderType::Compute:               shader_id = glCreateShader(GL_COMPUTE_SHADER);          break;
    case ShaderType::TesselationControl:    shader_id = glCreateShader(GL_TESS_CONTROL_SHADER);     break;
    case ShaderType::TesselationEvaluation: shader_id = glCreateShader(GL_TESS_EVALUATION_SHADER);  break;
    default: CHECK_FAIL( "File extensions was not recognised as shader type" );                     break;
    }

    return shader_id;
}
} // namespace graphics
} // namespace shake
