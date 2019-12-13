#ifndef VOXEL_GRID_HPP
#define VOXEL_GRID_HPP

#include <memory>
#include <array>

#include "shake/core/math/math.hpp"
#include "shake/core/std/array_3d.hpp"
#include "shake/core/macros/macro_property.hpp"
#include "shake/graphics/buffer_objects/ebo.hpp"
#include "shake/graphics/buffer_objects/vao.hpp"
#include "shake/graphics/buffer_objects/vbo.hpp"
#include "shake/graphics/geometry/geometry_3d.hpp"
#include "shake/graphics/material/texture.hpp"

namespace shake     {
namespace graphics  {

class VoxelGrid : public AGeometry3D
{
public:
    using Ptr = std::shared_ptr<VoxelGrid>;
public:
    VoxelGrid
    (
        const std::vector<float>    &   vertices,
        const std::vector<uint32_t> &   indices,
        const std::vector<float>    &   instances,
        const Texture::Ptr          &   palette
    );

    inline void set     ( const uint16_t x, const uint16_t y, const uint16_t z, glm::vec2 palette_coords)  { m_voxels.get(x,y,z) = { true, palette_coords }; }
    inline void remove  ( const uint16_t x, const uint16_t y, const uint16_t z)                            { m_voxels.get(x,y,z).on = false;                 }

    void update_buffers();

    bool is_occluded(const uint16_t x, const uint16_t y, const uint16_t z) const;

    virtual void draw() const override;

private:
    struct VoxelDefinition
    {
        bool        on;
        glm::vec2   palette_coords;
    };

    static constexpr       uint16_t    m_width     { 256 };
    static constexpr       uint16_t    m_height    { 256 };
    static constexpr       uint16_t    m_depth     { 256 };

    using Voxels = Array3D<VoxelDefinition, m_width, m_height, m_depth>;

private:
    Voxels                      m_voxels;
    PROPERTY_R( Vao,            vao     )
    Vbo                         m_vbo_voxel;
    Ebo                         m_ebo_voxel;
    Vbo                         m_vbo_instances;

    PROPERTY_R( uint32_t,       instance_count )
    PROPERTY_R( uint32_t,       index_count )

    PROPERTY_R( Texture::Ptr,   palette )
};

} // namespace graphics
} // namespace shake

#endif // VOXEL_GRID_HPP
