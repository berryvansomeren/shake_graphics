#include "camera.hpp"

//#include "shake/hid/keyboard.hpp"
//#include "shake/hid/mouse.hpp"

#include <algorithm>
#include <glad/glad.h>

namespace shake     {
namespace graphics  {

//----------------------------------------------------------------
Camera::Camera(size_t screen_width, size_t screen_height)
    : m_screen_width    { screen_width  }
    , m_screen_height   { screen_height }
    , m_keyboard_speed  { 0.01f }
    , m_mouse_speed     { 0.01f }
    , m_fov             { glm::radians(90.0f) }
    , m_transform       { std::make_shared<Transform3D>() }
{
    update_projection_matrix();

    m_transform->translate( { 0.f, -5.f, 100.f } );
}

//----------------------------------------------------------------
void Camera::update(float dt)
{
    float velocity { m_keyboard_speed * dt };

    // within camera space
    // y is up,
    // x is right,
    // the looking direction is -z

    /*const auto& keyboard = Keyboard::get_instance();
    const auto& mouse = Mouse::get_instance();

    if ( keyboard.is_down( Keyboard::Key::W ) ) { m_transform.translate( -math::axis::z * velocity );   }
    if ( keyboard.is_down( Keyboard::Key::S ) ) { m_transform.translate(  math::axis::z * velocity );   }
    if ( keyboard.is_down( Keyboard::Key::A ) ) { m_transform.translate( -math::axis::x * velocity );   }
    if ( keyboard.is_down( Keyboard::Key::D ) ) { m_transform.translate(  math::axis::x * velocity );   }
    if ( keyboard.is_down( Keyboard::Key::E ) ) { m_transform.translate(  math::axis::y * velocity );   }
    if ( keyboard.is_down( Keyboard::Key::Q ) ) { m_transform.translate( -math::axis::y * velocity );   }*/

    //if (keyboard::is_down(keyboard::Key::R)) { m_transform.roll_by  ( 1.0f );   }
    //if (keyboard::is_down(keyboard::Key::T)) { m_transform.pitch_by ( 1.0f );   }
    //if (keyboard::is_down(keyboard::Key::Y)) { m_transform.yaw_by   ( 1.0f );   }

    //if ( keyboard.is_down( Keyboard::Key::O ) ) { m_transform.set_translation(glm::vec3(0.f, 0.f, 0.f)); }

    //if(mouse.is_down( Mouse::Key::Left))
    //{
    //    // to prevent introducing rotation by pitching and yawing, you do yaw relative to world
    //    m_transform.yaw_world       ( -mouse.get_diff_x() * m_mouse_speed * dt );
    //    m_transform.pitch_relative  ( -mouse.get_diff_y() * m_mouse_speed * dt );
    //}

    //m_fov -= glm::radians(mouse.get_scroll_y());
    m_fov = glm::clamp(m_fov, glm::radians( 1.0f), glm::radians(90.0f));
    update_projection_matrix();
}

//----------------------------------------------------------------
void Camera::update_projection_matrix()
{
    const float aspect_ratio { static_cast<float>(m_screen_width) / static_cast<float>(m_screen_height) };
    m_projection = glm::perspective(m_fov, aspect_ratio, 0.1f, 1000.0f );
}

} // namespace graphics
} // namespace shake
