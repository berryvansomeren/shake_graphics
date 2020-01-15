#include "geometry_3d.hpp"

#include "shake/core/contracts/contracts.hpp"

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
std::shared_ptr<Geometry3D> make_geometry_3D
(
    const gl::PrimitiveType primitive_type,
    const std::vector<float>& vertex_data
)
{
    const auto vertex_format = VertexFormats::Pos3;
    const auto&& vao = make_vao( BindingPointSpecification { vertex_format, make_vbo( vertex_data ) } );
    const auto vertex_size = get_vertex_size_in_bytes( vertex_format );
    EXPECT( math::is_divisible_by( vertex_data.size(), *vertex_size ), "Vector of vertex floats has unexpected length." );
    const auto count = vertex_data.size() / *vertex_size;

    const auto result = std::make_shared<Geometry3D>
    (
        primitive_type,
        count, 
        vao
    );

    return result;
}

//----------------------------------------------------------------
#define DEFINE_MAKE_PRIMIMTIVE_3D( function_name, primitive_name ) \
    std::shared_ptr<Geometry3D> make_##function_name##_3D ( const std::vector<float>& vertices ) \
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

} // namespace gl
} // namespace shake
