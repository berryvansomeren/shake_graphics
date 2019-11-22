#ifndef DRAW_RENDER_PACK_HPP
#define DRAW_RENDER_PACK_HPP

#include "shake/core/math/transform_2d.hpp"
#include "shake/core/math/transform_3d.hpp"

//#include "shake/content/content_manager.hpp"

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

} // namespace graphics
} // namespace shake

#endif // DRAW_RENDER_PACK_HPP
