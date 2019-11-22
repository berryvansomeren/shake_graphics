#ifndef GRAPHICS_PRIMITIVE_3D_HPP
#define GRAPHICS_PRIMITIVE_3D_HPP

#include "shake/core/math/math.hpp"
#include "shake/core/types/macro_non_copyable.hpp"
#include "shake/core/types/macro_property.hpp"

#include "shake/graphics/geometry/geometry_3d.hpp"

#include "shake/graphics/buffer_objects/vao.hpp"
#include "shake/graphics/geometry/primitive_type.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class Primitive3D : public AGeometry3D
{
public:

    // A primitive is non-copyable,
    // because it relies on a Vao,
    // which is non-copyable.
    NON_COPYABLE( Primitive3D )

    Primitive3D
    (
        const PrimitiveType             primitive_type,
        const std::vector<float>&       vertices,
        const VertexFormat&             vertex_format = VertexFormats::Pos3
    );

    Primitive3D
    (
        const PrimitiveType             primitive_type,
        const std::vector<float>&       vertices,
        const std::vector<uint32_t>&    indices,
        const VertexFormat&             vertex_format = VertexFormats::Pos3
    );

    virtual void draw() const override;

public:
    virtual ~Primitive3D() override = default;

private:
    PROPERTY_R( PrimitiveType,  type                )
    PROPERTY_R( bool,           has_index_buffer    )
    PROPERTY_R( size_t,         count               )
    PROPERTY_R( Vao,            vao                 )
};

//----------------------------------------------------------------
#define DEFINE_PRIMITIVE_3D_CLASS( classname ) \
    class classname##3D : public Primitive3D \
    { \
    public: \
        classname##3D( const std::vector<float>& vertices ) \
            : Primitive3D \
        ( \
            PrimitiveType::classname, \
            vertices \
        ) \
        { } \
        \
        classname##3D( const std::vector<glm::vec3>& vertices ) \
            : Primitive3D \
        ( \
            PrimitiveType::classname, \
            math::convert_to_vector_of_floats( vertices ) \
        ) \
        { } \
    };

DEFINE_PRIMITIVE_3D_CLASS( Lines            )
DEFINE_PRIMITIVE_3D_CLASS( LineStrip        )
DEFINE_PRIMITIVE_3D_CLASS( LineLoop         )

DEFINE_PRIMITIVE_3D_CLASS( Triangles        )
DEFINE_PRIMITIVE_3D_CLASS( TriangleStrip    )
DEFINE_PRIMITIVE_3D_CLASS( TriangleFan      )

#undef DEFINE_GEOMETRY_3D_CLASS

} // namespace graphics
} // namespace shake

#endif // PRIMITIVE_3D_HPP
