#include "geometry_3d.hpp"

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/std/vector.hpp"

#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/draw.hpp"


namespace shake {
namespace graphics {

//----------------------------------------------------------------
Geometry3D::Geometry3D
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
Geometry3D make_geometry_3D
(
    const gl::PrimitiveType primitive_type,
    const std::vector<float>& vertex_data
)
{
    const auto vertex_format = VertexFormats::Pos3;
    const auto vbo_sptr = std::make_shared<Vbo>( make_vbo( vertex_data ) );
    const auto vao_sptr = std::make_shared<Vao>( make_vao( BindingPointSpecification { vertex_format, vbo_sptr } ) );

    const auto vertex_data_size_in_bytes = get_size_in_bytes( vertex_data );
    const auto vertex_size_in_bytes = get_vertex_size_in_bytes( vertex_format );
    EXPECT( math::is_divisible_by( vertex_data_size_in_bytes, *vertex_size_in_bytes ), "Vector of vertex floats has unexpected length." );
    const auto vertex_count = vertex_data_size_in_bytes / *vertex_size_in_bytes;

    const auto geometry_3d = Geometry3D
    {
        primitive_type,
        vertex_count, 
        vao_sptr
    };

    return geometry_3d;
}

//----------------------------------------------------------------
#define DEFINE_MAKE_PRIMIMTIVE_3D( function_name, primitive_name ) \
    Geometry3D make_##function_name##_3D ( const std::vector<float>& vertices ) \
    { \
        return make_geometry_3D \
        ( \
            gl::PrimitiveType::primitive_name, \
            vertices \
        ); \
    } \

//----------------------------------------------------------------
DEFINE_MAKE_PRIMIMTIVE_3D( lines,           Lines           )
DEFINE_MAKE_PRIMIMTIVE_3D( line_strip,      LineStrip       )
DEFINE_MAKE_PRIMIMTIVE_3D( line_loop,       LineLoop        )

DEFINE_MAKE_PRIMIMTIVE_3D( triangles,       Triangles       )
DEFINE_MAKE_PRIMIMTIVE_3D( triangle_strip,  TriangleStrip   )
DEFINE_MAKE_PRIMIMTIVE_3D( triangle_fan,    TriangleFan     )

#undef DEFINE_MAKE_PRIMIMTIVE_3D

} // namespace gl
} // namespace shake
