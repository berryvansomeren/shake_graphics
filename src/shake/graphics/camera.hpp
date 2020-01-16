#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <memory>

#include "shake/core/math/math.hpp"
#include "shake/core/math/transform_3d.hpp"

namespace shake     {
namespace graphics  {

class Camera
{
public:
    Camera
    (
        size_t      screen_width,
        size_t      screen_height
    );

    void update(float dt);

    const std::shared_ptr<Transform3D>   get_transform()         const { return m_transform;     }
          std::shared_ptr<Transform3D>   get_transform()               { return m_transform;     }

    inline       glm::mat4      get_projection_matrix() const { return m_projection;    }

    inline       glm::mat4      get_view_matrix()       const
    {
        return glm::inverse(m_transform->get_matrix());
    }

protected:
    void update_projection_matrix();

private:
    size_t      m_screen_width;
    size_t      m_screen_height;
    float       m_fov;

    float       m_keyboard_speed;
    float       m_mouse_speed;

    std::shared_ptr<Transform3D> m_transform;
    glm::mat4   m_projection;
};

} // namespace graphics
} // namespace shake

#endif // CAMERA_HPP
