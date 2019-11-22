#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include "shake/core/math/math.hpp"
#include "shake/graphics/camera.hpp"
#include "shake/graphics/material/shader.hpp"

namespace shake     {
namespace graphics  {

void            set_current_screen_size ( const glm::vec2& size );
glm::vec2       get_current_screen_size ( );

void            set_current_camera ( const Camera::Ptr& camera );
Camera::Ptr&    get_current_camera ( );

void            set_current_ortho_projection ( const glm::mat4& ortho_projection );
glm::mat4       get_current_ortho_projection ( );

} // namespace graphics
} // namespace shake

#endif // GRAPHICS_CONTEXT_HPP
