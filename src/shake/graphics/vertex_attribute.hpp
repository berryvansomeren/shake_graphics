#ifndef VERTEX_ATTRIBUTE_HPP
#define VERTEX_ATTRIBUTE_HPP

#include <glad/glad.h>
#include <cstdint>

namespace shake {
namespace graphics {

class VertexAttribute
{
public:
    enum class Location : uint8_t
    {
        VertexPos2  = 0,
        VertexTex2  = 1,

        VertexPos3  = 2,
        VertexNorm  = 3,

        VoxelIdx3   = 4,
        VoxelTex2   = 5
    };

    enum class Size     : uint8_t { _1 = 1, _2 = 2, _3 = 3, _4 = 4 };
    enum class Type     : GLenum  { Float = GL_FLOAT };

public:

    VertexAttribute();

    void specify
    (
        Location    location,
        Size        size,
        uint32_t    stride,
        uint32_t    offset
    );

    // We dont store the location locally,
    // but instead, pass it as a parameter
    // since the VAO which manages the vertex attributes,
    // knows the correct location already.
    void enable         ( Location location );
    void disable        ( Location location );
    void set_divisor    ( Location location, const uint32_t divisor );

private:
    bool        m_is_specified;
    bool        m_is_enabled;
};

} // namespace graphics
} // namespace shake

#endif // VERTEX_ATTRIBUTE_HPP
