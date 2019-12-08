#ifndef VERTEX_ATTRIBUTE_HPP
#define VERTEX_ATTRIBUTE_HPP

#include <cstdint>

#include "shake/graphics/gl/gl_enum.hpp"

namespace shake {
namespace graphics {

class VertexAttribute
{
public:
   
    enum class Size     : uint8_t { _1 = 1, _2 = 2, _3 = 3, _4 = 4 };

public:

    VertexAttribute();

    void specify
    (
        gl::VertexAttributeIndex location,
        Size        size,
        uint32_t    stride,
        uint32_t    offset
    );

    // We dont store the location locally,
    // but instead, pass it as a parameter
    // since the VAO which manages the vertex attributes,
    // knows the correct location already.
    void enable         ( gl::VertexAttributeIndex location );
    void disable        ( gl::VertexAttributeIndex location );
    void set_divisor    ( gl::VertexAttributeIndex location, const uint32_t divisor );

private:
    bool        m_is_specified;
    bool        m_is_enabled;
};

} // namespace graphics
} // namespace shake

#endif // VERTEX_ATTRIBUTE_HPP
