#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <memory>

#include "shake/core/math/math.hpp"
#include "shake/core/types/underlying_cast.hpp"

#include "shake/graphics/material/cube_map.hpp"
#include "shake/graphics/material/shader.hpp"
#include "shake/graphics/material/texture.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
struct AUniform
{
    using Ptr = std::unique_ptr<AUniform>;

    virtual ~AUniform();
    virtual void bind( const Shader::Ptr& shader, int32_t uniform_location ) const = 0;
};

//----------------------------------------------------------------
#define DEFINE_UNIFORM_CLASS( name, uniform_type ) \
    class Uniform##name : public AUniform \
    { \
    public: \
        Uniform##name ( uniform_type value ); \
        \
        virtual void bind( const Shader::Ptr& shader, int32_t uniform_location ) const override \
        { \
            shader->set_uniform( uniform_location, m_value ); \
        } \
        \
    private: \
        uniform_type m_value; \
    };

DEFINE_UNIFORM_CLASS( Int32,   int32_t     )
DEFINE_UNIFORM_CLASS( Float,   float       )
DEFINE_UNIFORM_CLASS( Vec2,    glm::vec2   )
DEFINE_UNIFORM_CLASS( Vec3,    glm::vec3   )
DEFINE_UNIFORM_CLASS( Mat4,    glm::mat4   )

#undef DEFINE_UNIFORM_STRUCT

//----------------------------------------------------------------
class UniformTexture : public AUniform
{
public:
    UniformTexture
    (
        const Texture::Ptr& texture,
              TextureUnit   texture_unit
    )
        : m_texture         { texture }
        , m_texture_unit    { texture_unit }
    { }

    virtual void bind( const Shader::Ptr& shader, int32_t uniform_location ) const override
    {
        m_texture->bind( m_texture_unit );
        shader->set_uniform( uniform_location, static_cast<int32_t>( underlying_cast( m_texture_unit ) ) );
    }

private:
    Texture::Ptr    m_texture;
    TextureUnit     m_texture_unit;
};

//----------------------------------------------------------------
class UniformCubeMap : public AUniform
{
public:
    UniformCubeMap
    (
        const CubeMap::Ptr& cube_map,
              TextureUnit   texture_unit
    )
        : m_cube_map { cube_map }
        , m_texture_unit { texture_unit }
    { }

    virtual void bind( const Shader::Ptr& shader, int32_t uniform_location ) const override
    {
        m_cube_map->bind( m_texture_unit );
        shader->set_uniform( uniform_location, static_cast<int32_t>( underlying_cast( m_texture_unit ) ) );
    }

private:
    CubeMap::Ptr    m_cube_map;
    TextureUnit     m_texture_unit;
};

} // namespace graphics
} // namespace shake

#endif // UNIFORM_HPP
