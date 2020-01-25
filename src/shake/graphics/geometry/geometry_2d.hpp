#ifndef GRAPHICS_GEOMETRY_2D_HPP
#define GRAPHICS_GEOMETRY_2D_HPP

#include "shake/core/math/math.hpp"
#include "shake/core/math/coordinates.hpp"
#include "shake/core/macros/macro_non_copyable.hpp"
#include "shake/core/macros/macro_property.hpp"

#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/buffer_objects/vao.hpp"
#include "shake/graphics/buffer_objects/vertex_format.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class Geometry2D
{
public:
    Geometry2D
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
Geometry2D make_geometry_2D
(
    const gl::PrimitiveType primitive_type,
    const std::vector<float>& vertex_data
);

//----------------------------------------------------------------
#define DECLARE_MAKE_GEOMETRY_2D( function_name, primitive_name ) \
    Geometry2D make_##function_name##_2D ( const std::vector<float>& vertices );

//----------------------------------------------------------------
DECLARE_MAKE_GEOMETRY_2D( lines,            Lines            )
DECLARE_MAKE_GEOMETRY_2D( line_strip,       LineStrip        )
DECLARE_MAKE_GEOMETRY_2D( line_loop,        LineLoop         )

DECLARE_MAKE_GEOMETRY_2D( triangles,        Triangles        )
DECLARE_MAKE_GEOMETRY_2D( triangle_strip,   TriangleStrip    )
DECLARE_MAKE_GEOMETRY_2D( triangle_fan,     TriangleFan      )

#undef DECLARE_MAKE_GEOMETRY_2D

//----------------------------------------------------------------
Geometry2D make_rectangle_2D( const float& width, const float& height );

//----------------------------------------------------------------
Geometry2D make_circle_filled_2D( const float& radius );

} // namespace graphics
} // namespace shake

#endif // GRAPHICS_GEOMETRY_2D_HPP
