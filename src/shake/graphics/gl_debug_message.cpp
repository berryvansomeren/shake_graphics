#include "gl_debug_message.hpp"

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/log.hpp"

namespace shake {
namespace graphics {
namespace gl {
namespace debug_message {

namespace { // anonymous

std::string source_to_string( GLenum source )
{
    switch ( source )
    {
    case GL_DEBUG_SOURCE_API               : return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM     : return "Window System";
    case GL_DEBUG_SOURCE_SHADER_COMPILER   : return "Shader Compiler";
    case GL_DEBUG_SOURCE_THIRD_PARTY       : return "Third Party";
    case GL_DEBUG_SOURCE_APPLICATION       : return "Application";
    case GL_DEBUG_SOURCE_OTHER             : return "Other";
    default:
        CHECK_FAIL( "Unknown source GLenum" );
        return "Shake Error";
    }
}

std::string type_to_string( GLenum type )
{
    switch ( type )
    {
    case GL_DEBUG_TYPE_ERROR               : return "Error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR : return "Deprecated Behavior";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  : return "Undefined Behavior";
    case GL_DEBUG_TYPE_PORTABILITY         : return "Portability";
    case GL_DEBUG_TYPE_PERFORMANCE         : return "Performance";
    case GL_DEBUG_TYPE_MARKER              : return "Marker";
    case GL_DEBUG_TYPE_PUSH_GROUP          : return "Push Group";
    case GL_DEBUG_TYPE_POP_GROUP           : return "Pop Group";
    case GL_DEBUG_TYPE_OTHER               : return "Other";
    default:
        CHECK_FAIL( "Unknown type GLenum" );
        return "Shake Error";
    }
}

std::string severity_to_string( GLenum severity )
{
    switch ( severity )
    {
    case GL_DEBUG_SEVERITY_HIGH            : return "High";
    case GL_DEBUG_SEVERITY_MEDIUM          : return "Medium";
    case GL_DEBUG_SEVERITY_LOW             : return "Low";
    case GL_DEBUG_SEVERITY_NOTIFICATION    : return "Notification";
    default:
        CHECK_FAIL( "Unknown severity GLenum" );
        return "Shake Error";
    }
}

std::string to_string
(
    GLenum          source,
    GLenum          type,
    GLuint          id,
    GLenum          severity,
    GLsizei         length,
    const GLchar*   message,
    const void*     userParam
)
{
    std::string message_str = length < 0
            ? std::string( message )            // null terminated string
            : std::string( message, length );   // not null terminated

    std::string result
    {
        "GL DEBUG MESSAGE: "
        "source: "      + source_to_string( source )        +
        ", type: "        + type_to_string( type )          +
        ", id: "          + std::to_string( id )            +
        ", severity: "    + severity_to_string( severity )  +
        ", message: "     + message_str
    };

    return result;
}

} // namespace anonymous

void callback
(
    GLenum          source,
    GLenum          type,
    GLuint          id,
    GLenum          severity,
    GLsizei         length,
    const GLchar*   message,
    const void*     userParam
)
{
    if ( type == GL_DEBUG_TYPE_ERROR )
    {
        const std::string message_str { to_string( source, type, id, severity, length, message, userParam ) };
        LOG( message_str );
        CHECK_FAIL( "An OpenGL error occurred." );
    }
}

} // namespace debug_message
} // namespace gl
} // namespace graphics
} // namespace shake
