#ifndef GRAPHICS_PRIMITIVE_2D_HPP
#define GRAPHICS_PRIMITIVE_2D_HPP

#include "shake/core/math/math.hpp"
#include "shake/core/math/coordinates.hpp"
#include "shake/core/macros/macro_non_copyable.hpp"
#include "shake/core/macros/macro_property.hpp"

#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/geometry/geometry_2d.hpp"
#include "shake/graphics/vertex_format.hpp"
#include "shake/graphics/buffer_objects/vao.hpp"
#include "shake/graphics/geometry/primitive_type.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class Primitive2D : public AGeometry2D
{
public:

    // A primitive is non-copyable,
    // because it relies on a Vao,
    // which is non-copyable.
    NON_COPYABLE( Primitive2D )

    Primitive2D
    (
        const gl::PrimitiveType         primitive_type,
        const std::vector<float>&       vertices,
        const VertexFormat&             vertex_format = VertexFormats::Pos2
    );

    Primitive2D
    (
        const gl::PrimitiveType         primitive_type,
        const std::vector<float>&       vertices,
        const std::vector<uint32_t>&    indices,
        const VertexFormat&             vertex_format = VertexFormats::Pos2
    );

    virtual void draw() const override;

private:
    PROPERTY_R( gl::PrimitiveType,  type                )
    PROPERTY_R( bool,               has_index_buffer    )
    PROPERTY_R( size_t,             count               )
    PROPERTY_R( Vao,                vao                 )
};


//----------------------------------------------------------------
#define DEFINE_PRIMITIVE_2D_CLASS( classname ) \
    class classname##2D : public Primitive2D \
    { \
    public: \
        classname##2D( const std::vector<glm::vec2>& points ) \
            : Primitive2D \
        ( \
            gl::PrimitiveType::classname, \
            math::convert_to_vector_of_floats( points ) \
        ) \
        { } \
    };

DEFINE_PRIMITIVE_2D_CLASS( Lines            )
DEFINE_PRIMITIVE_2D_CLASS( LineStrip        )
DEFINE_PRIMITIVE_2D_CLASS( LineLoop         )

DEFINE_PRIMITIVE_2D_CLASS( Triangles        )
DEFINE_PRIMITIVE_2D_CLASS( TriangleStrip    )
DEFINE_PRIMITIVE_2D_CLASS( TriangleFan      )

#undef DEFINE_GEOMETRY_2D_CLASS

//----------------------------------------------------------------
class Rectangle2D : public Primitive2D
{
public:
    Rectangle2D( const float& width, const float& height )
    : Primitive2D
    (
        gl::PrimitiveType::TriangleFan,
        compute_vertices( width, height ),
        VertexFormats::Pos2Tex2
    )
    { }

private:
    std::vector<float> compute_vertices( const float& width, const float& height )
    {
        return
        {
            // positions    // texture coordinates
            0.f,    0.f,    0.f, 1.f,   // bottom-left
            width,  0.f,    1.f, 1.f,   // bottom-right
            width,  height, 1.f, 0.f,   // top-right
            0.f,    height, 0.f, 0.f    // top-left
        };
    }
};

//----------------------------------------------------------------
class CircleFilled2D : public Primitive2D
{
public:
    CircleFilled2D( const float& radius )
    : Primitive2D
    (
        gl::PrimitiveType::TriangleFan,
        compute_vertices( radius )
    )
    { }

private:
    std::vector<float> compute_vertices( const float& radius )
    {
        auto vertices = std::vector<float> { };

        constexpr auto total_radians        = 2.f * math::pi_f;
        constexpr auto increment_radians    = total_radians / 32.f;

        for( size_t i = 0; i < 32; ++i )
        {
            const auto angle = i * increment_radians;
            const auto& cartesian = coordinates::convert_polar_to_cartesian( radius, angle );
            vertices.emplace_back( cartesian.x );
            vertices.emplace_back( cartesian.y );
        };

        return vertices;
    }
};



} // namespace graphics
} // namespace shake

#endif // GRAPHICS_PRIMITIVE_2D_HPP
