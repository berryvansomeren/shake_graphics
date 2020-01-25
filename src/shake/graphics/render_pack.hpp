#ifndef RENDER_PACK_HPP
#define RENDER_PACK_HPP

#include <memory>

#include "shake/graphics/geometry/geometry_2d.hpp"
#include "shake/graphics/geometry/geometry_3d.hpp"
#include "shake/graphics/material/material.hpp"

namespace shake     {
namespace graphics  {

//----------------------------------------------------------------
struct RenderPack2D
{
    const std::shared_ptr<Geometry2D>    geometry;
    const std::shared_ptr<Material>      material;
};

//----------------------------------------------------------------
struct RenderPack3D
{
    const std::shared_ptr<Geometry3D>   geometry;
    const std::shared_ptr<Material>     material;
};

} // namespace graphics
} // namespace shake

#endif // RENDER_PACK_HPP
