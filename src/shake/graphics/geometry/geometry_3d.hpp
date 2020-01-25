#ifndef GRAPHICS_GEOMETRY_3D_HPP
#define GRAPHICS_GEOMETRY_3D_HPP

#include "shake/core/math/math.hpp"
#include "shake/core/macros/macro_non_copyable.hpp"
#include "shake/core/macros/macro_property.hpp"

#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/buffer_objects/vao.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class Geometry3D
{
public:
    Geometry3D
    (
        const gl::PrimitiveType     type,
        const std::size_t           count,
        const std::shared_ptr<Vao>  vao
    );

private:
    PROPERTY_R( gl::PrimitiveType,      type    )
    PROPERTY_R( std::size_t,            count   )
    PROPERTY_R( std::shared_ptr<Vao>,   vao     )
};

//----------------------------------------------------------------
Geometry3D make_geometry_3D
(
    const gl::PrimitiveType primitive_type,
    const std::vector<float>& vertex_data
);

//----------------------------------------------------------------
#define DECLARE_MAKE_GEOMETRY_3D( function_name, primitive_name ) \
    Geometry3D make_##function_name##_3D ( const std::vector<float>& vertices );

//----------------------------------------------------------------
DECLARE_MAKE_GEOMETRY_3D( lines,           Lines           )
DECLARE_MAKE_GEOMETRY_3D( line_strip,      LineStrip       )
DECLARE_MAKE_GEOMETRY_3D( line_loop,       LineLoop        )

DECLARE_MAKE_GEOMETRY_3D( triangles,       Triangles       )
DECLARE_MAKE_GEOMETRY_3D( triangle_strip,  TriangleStrip   )
DECLARE_MAKE_GEOMETRY_3D( triangle_fan,    TriangleFan     )

#undef DECLARE_MAKE_GEOMETRY_3D

} // namespace graphics
} // namespace shake

#endif // GRAPHICS_GEOMETRY_3D_HPP
