#include "voxel_grid.hpp"

#include "shake/graphics/gl.hpp"

namespace shake     {
namespace graphics  {

//----------------------------------------------------------------
VoxelGrid::VoxelGrid
(
    const std::vector<float>    &   vertices,
    const std::vector<uint32_t> &   indices,
    const std::vector<float>    &   instances,
    const Texture::Ptr          &   palette
)
    : m_index_count { static_cast<uint32_t>( indices.size() ) }
    , m_palette     { palette }
{
    // we will first configure the vao properly
    m_vao.bind();

    // set vertex data
    m_vbo_voxel.bind();
    m_vbo_voxel.set_data(vertices);

    // set index data
    m_ebo_voxel.bind();
    m_ebo_voxel.set_data(indices);
    m_vao.specify_enable_vertex_format( VertexFormats::Pos3Nor3 );

    // set instance data
    m_vbo_instances.bind();
    m_vao.specify_enable_vertex_format_instanced( VertexFormats::VoxelIdx3Tex2 );

    // vao is now finished
    m_vao.unbind();

    for (uint16_t z { 0 }; z < m_depth; ++z)
    {
        for (uint16_t y { 0 }; y < m_height; ++y)
        {
            for (uint16_t x { 0 }; x < m_width; ++x)
            {
                m_voxels.get(x, y, z).on = false;
            }
        }
    }

    for ( size_t i { 0 }; i < instances.size(); i+=5 )
    {
        const float x         { instances[i+0] };
        const float y         { instances[i+1] };
        const float z         { instances[i+2] };
        const float palette_x { instances[i+3] };
        const float palette_y { instances[i+4] };
        set(x, y, z, glm::vec2{palette_x, palette_y});
    }

    update_buffers();
}

//----------------------------------------------------------------
void VoxelGrid::update_buffers()
{
    std::vector<float> instance_data { };
    for (uint16_t z { 0 }; z < m_depth; ++z)
    {
        for (uint16_t y { 0 }; y < m_height; ++y)
        {
            for (uint16_t x { 0 }; x < m_width; ++x)
            {
                const VoxelDefinition& voxel = m_voxels.get(x, y, z);
                if( voxel.on && !is_occluded( x, y, z) )
                {
                    instance_data.emplace_back(static_cast<float>(x));
                    instance_data.emplace_back(static_cast<float>(y));
                    instance_data.emplace_back(static_cast<float>(z));
                    instance_data.emplace_back(voxel.palette_coords.x);
                    instance_data.emplace_back(voxel.palette_coords.y);
                }
            }
        }
    }
    m_vbo_instances.bind();
    m_vbo_instances.set_data(instance_data);
    m_vbo_instances.unbind();

    m_instance_count = instance_data.size() / 5;
}

//----------------------------------------------------------------
bool VoxelGrid::is_occluded(const uint16_t x, const uint16_t y, const uint16_t z) const
{
    // right
    if ( x + 1 >= m_width )                 { return false; }
    if ( !m_voxels.get(x + 1, y, z).on )    { return false; }

    // left
    if ( x - 1 < 0 )                        { return false; }
    if ( !m_voxels.get(x - 1, y, z).on )    { return false; }

    // top
    if ( y + 1 >= m_height )                { return false; }
    if ( !m_voxels.get(x, y + 1, z).on )    { return false; }

    // bottom
    if ( y - 1 < 0 )                        { return false; }
    if ( !m_voxels.get(x, y - 1, z).on )    { return false; }

    // back
    if ( z + 1 >= m_depth )                 { return false; }
    if ( !m_voxels.get(x, y, z + 1).on )    { return false; }

    // front
    if ( z - 1 < 0 )                        { return false; }
    if ( !m_voxels.get(x, y, z - 1).on )    { return false; }

    return true;
}

//----------------------------------------------------------------
void VoxelGrid::draw() const
{
    m_vao.bind();
    gl::draw_elements_instanced
    (
        PrimitiveType::Triangles,
        m_index_count,
        m_instance_count
    );
    m_vao.unbind();
}

} // namespace graphics
} // namespace shake
