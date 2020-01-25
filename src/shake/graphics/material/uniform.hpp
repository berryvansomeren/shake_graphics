#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <memory>
#include <variant>

#include "shake/core/math/math.hpp"
#include "shake/core/type_traits/underlying_cast.hpp"

#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/material/cube_map.hpp"
#include "shake/graphics/material/program.hpp"
#include "shake/graphics/material/texture.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class UniformTexture
{
public:
    UniformTexture
    (
        const std::shared_ptr<Texture>& texture,
              gl::TextureUnitIndex   texture_unit
    )
        : m_texture         { texture }
        , m_texture_unit    { texture_unit }
    { }

private:
    std::shared_ptr<Texture> m_texture;
    gl::TextureUnitIndex     m_texture_unit;
};

//----------------------------------------------------------------
class UniformCubeMap
{
public:
    UniformCubeMap
    (
        const std::shared_ptr<CubeMap>& cube_map,
              gl::TextureUnitIndex   texture_unit
    )
        : m_cube_map { cube_map }
        , m_texture_unit { texture_unit }
    { }

private:
    std::shared_ptr<CubeMap> m_cube_map;
    gl::TextureUnitIndex     m_texture_unit;
};

//----------------------------------------------------------------
//using Uniform = std::variant
//<
//    std::int32_t,
//    float,
//    glm::vec2,
//    glm::vec3,
//    glm::mat4,
//    UniformTexture,
//    UniformCubeMap
//>;

} // namespace graphics
} // namespace shake

#endif // UNIFORM_HPP
