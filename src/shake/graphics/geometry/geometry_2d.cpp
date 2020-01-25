#include "geometry_2d.hpp"

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/std/vector.hpp"

#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/draw.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
Geometry2D::Geometry2D
(
    const gl::PrimitiveType     type,
    const std::size_t           count,
    const std::shared_ptr<Vao>  vao
)
: m_type  { type    }
, m_count { count   }
, m_vao   { vao     }
{ }

//----------------------------------------------------------------
Geometry2D make_geometry_2D
(
    const gl::PrimitiveType primitive_type,
    const std::vector<float>& vertex_data
)
{
    const auto vertex_format = VertexFormats::Pos2;
    const auto vbo_sptr = std::make_shared<Vbo>( make_vbo( vertex_data ) );
    const auto vao_sptr = std::make_shared<Vao>( make_vao( BindingPointSpecification { vertex_format, vbo_sptr } ) );
    
    const auto vertex_data_size_in_bytes = get_size_in_bytes( vertex_data );
    const auto vertex_size_in_bytes = get_vertex_size_in_bytes( vertex_format );
    EXPECT( math::is_divisible_by( vertex_data_size_in_bytes, *vertex_size_in_bytes ), "Vector of vertex floats has unexpected length." );
    const auto vertex_count = vertex_data_size_in_bytes / *vertex_size_in_bytes;

    auto geometry_3d = Geometry2D
    {
        primitive_type,
        vertex_count, 
        vao_sptr
    };

    return geometry_3d;
}

//----------------------------------------------------------------
#define DEFINE_MAKE_PRIMIMTIVE_2D( function_name, primitive_name ) \
    Geometry2D make_##function_name##_2D ( const std::vector<float>& vertices ) \
    { \
        return make_geometry_2D \
        ( \
            gl::PrimitiveType::primitive_name, \
            vertices \
        ); \
    } \

//----------------------------------------------------------------
DEFINE_MAKE_PRIMIMTIVE_2D( lines,           Lines           )
DEFINE_MAKE_PRIMIMTIVE_2D( line_strip,      LineStrip       )
DEFINE_MAKE_PRIMIMTIVE_2D( line_loop,       LineLoop        )

DEFINE_MAKE_PRIMIMTIVE_2D( triangles,       Triangles       )
DEFINE_MAKE_PRIMIMTIVE_2D( triangle_strip,  TriangleStrip   )
DEFINE_MAKE_PRIMIMTIVE_2D( triangle_fan,    TriangleFan     )

#undef DEFINE_MAKE_PRIMIMTIVE_2D

//----------------------------------------------------------------
Geometry2D make_rectangle_2D( const float& width, const float& height )
{
    const auto primitive_type = gl::PrimitiveType::TriangleFan;
    const auto vertices = std::vector<float>
    {
        // positions    // texture coordinates
        0.f,    0.f,    0.f, 1.f,   // bottom-left
        width,  0.f,    1.f, 1.f,   // bottom-right
        width,  height, 1.f, 0.f,   // top-right
        0.f,    height, 0.f, 0.f    // top-left
    };

    return make_geometry_2D( primitive_type, vertices );
}

//----------------------------------------------------------------
Geometry2D make_circle_filled_2D( const float& radius )
{
    const auto primitive_type = gl::PrimitiveType::TriangleFan;

    constexpr auto n_vertices           = 128;
    constexpr auto total_radians        = 2.f * math::pi_f;
    constexpr auto increment_radians    = total_radians / n_vertices;
    
    auto vertices = std::vector<float> { };
    for( size_t i = 0; i <= n_vertices; ++i )
    {
        const auto angle = i * increment_radians;
        const auto& cartesian = coordinates::convert_polar_to_cartesian( radius, angle );
        vertices.emplace_back( cartesian.x );
        vertices.emplace_back( cartesian.y );
    };

    return make_geometry_2D( primitive_type, vertices );
}

} // namespace graphics
} // namespace shake
