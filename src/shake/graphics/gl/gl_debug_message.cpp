#include "gl_debug_message.hpp"

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/log.hpp"

#include "shake/core/macros/macro_define_mapping.hpp"

#include "shake/core/std/map.hpp"

namespace shake {
namespace graphics {
namespace gl {
namespace debug_message {

namespace { // anonymous

//----------------------------------------------------------------
DEFINE_MAPPING( std::string, source_to_string, GLenum,
    { GL_DEBUG_SOURCE_API               , "API"             },
    { GL_DEBUG_SOURCE_WINDOW_SYSTEM     , "Window System"   },
    { GL_DEBUG_SOURCE_SHADER_COMPILER   , "Shader Compiler" },
    { GL_DEBUG_SOURCE_THIRD_PARTY       , "Third Party"     },
    { GL_DEBUG_SOURCE_APPLICATION       , "Application"     },
    { GL_DEBUG_SOURCE_OTHER             , "Other"           }
)

//----------------------------------------------------------------
DEFINE_MAPPING( std::string, type_to_string, GLenum,
    { GL_DEBUG_TYPE_ERROR               , "Error"               },
    { GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR , "Deprecated Behavior" },
    { GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  , "Undefined Behavior"  },
    { GL_DEBUG_TYPE_PORTABILITY         , "Portability"         },
    { GL_DEBUG_TYPE_PERFORMANCE         , "Performance"         },
    { GL_DEBUG_TYPE_MARKER              , "Marker"              },
    { GL_DEBUG_TYPE_PUSH_GROUP          , "Push Group"          },
    { GL_DEBUG_TYPE_POP_GROUP           , "Pop Group"           },
    { GL_DEBUG_TYPE_OTHER               , "Other"               }
)

//----------------------------------------------------------------
DEFINE_MAPPING( std::string, severity_to_string, GLenum,
    { GL_DEBUG_SEVERITY_HIGH            , "High"            },
    { GL_DEBUG_SEVERITY_MEDIUM          , "Medium"          },
    { GL_DEBUG_SEVERITY_LOW             , "Low"             },
    { GL_DEBUG_SEVERITY_NOTIFICATION    , "Notification"    }
)


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
        ", type: "      + type_to_string( type )            +
        ", id: "        + std::to_string( id )              +
        ", severity: "  + severity_to_string( severity )    +
        ", message: "   + message_str
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
