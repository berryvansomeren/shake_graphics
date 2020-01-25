#ifndef DRAW_RENDER_PACK_HPP
#define DRAW_RENDER_PACK_HPP

#include <memory>

#include "shake/core/math/transform_2d.hpp"
#include "shake/core/math/transform_3d.hpp"
#include "shake/graphics/geometry/geometry_2d.hpp"
#include "shake/graphics/geometry/geometry_3d.hpp"
#include "shake/graphics/render_pack.hpp"


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

//----------------------------------------------------------------
void draw( const std::shared_ptr<Geometry2D>& primitive );

//----------------------------------------------------------------
void draw( const std::shared_ptr<Geometry3D>& primitive );

} // namespace graphics
} // namespace shake

#endif // DRAW_RENDER_PACK_HPP
