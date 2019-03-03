#ifndef GL_DEBUG_MESSAGE_HPP
#define GL_DEBUG_MESSAGE_HPP

#include <string>

#include <glad/glad.h>

#include "shake/core/contracts/contracts.hpp"

namespace shake {
namespace graphics {
namespace gl {
namespace debug_message {

void callback
(
    GLenum          source,
    GLenum          type,
    GLuint          id,
    GLenum          severity,
    GLsizei         length,
    const GLchar*   message,
    const void*     userParam
);

} // namespace debug_message
} // namespace gl
} // namespace graphics
} // namespace shake

#endif // GL_DEBUG_MESSAGE_HPP
