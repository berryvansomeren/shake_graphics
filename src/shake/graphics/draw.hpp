#ifndef DRAW_RENDER_PACK_HPP
#define DRAW_RENDER_PACK_HPP

#include "shake/graphics/gl/gl.hpp"

#include "shake/core/math/transform_2d.hpp"
#include "shake/core/math/transform_3d.hpp"



//#include "shake/content/content_manager.hpp"

#include "shake/graphics/render_pack.hpp"

#include "shake/graphics/geometry/primitive_2d.hpp"
#include "shake/graphics/geometry/primitive_3d.hpp"


namespace shake     {
namespace graphics  {

//----------------------------------------------------------------
void draw
(
    const RenderPack2D& render_pack,
    const Transform2D&  transform
);

//----------------------------------------------------------------
void draw
(
    const RenderPack3D& render_pack,
    const Transform3D&  transform
);

void draw( const Primitive2D& primitive );
void draw( const Primitive3D& primitive );

} // namespace graphics
} // namespace shake

#endif // DRAW_RENDER_PACK_HPP
