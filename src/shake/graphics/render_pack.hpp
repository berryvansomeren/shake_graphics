#ifndef RENDER_PACK_HPP
#define RENDER_PACK_HPP

#include <memory>

#include "shake/graphics/geometry/geometry_2d.hpp"
#include "shake/graphics/geometry/geometry_3d.hpp"
#include "shake/graphics/material/material.hpp"

namespace shake     {
namespace graphics  {

struct RenderPack3D
{
    const AGeometry3D::Ptr  geometry;
    const Material::Ptr     material;
};

struct RenderPack2D
{
    const AGeometry2D::Ptr  geometry;
    const Material::Ptr     material;
};

} // namespace graphics
} // namespace shake

#endif // RENDER_PACK_HPP
