#ifndef PRIMITIVE_TYPE_HPP
#define PRIMITIVE_TYPE_HPP

namespace shake {
namespace graphics {

enum class PrimitiveType
{
    Lines,
    LineStrip,
    LineLoop,

    Triangles,
    TriangleStrip,
    TriangleFan
};

} // namespace graphics
} // namespace shake

#endif // PRIMITIVE_TYPE_HPP
