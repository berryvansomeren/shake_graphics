#include "primitive_3d.hpp"

#include "shake/core/contracts/contracts.hpp"

#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/draw.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
Primitive3D::Primitive3D
(
    const gl::PrimitiveType         primitive_type,
    const std::vector<float>&   vertices,
    const VertexFormat&         vertex_format
)
    : m_type  { primitive_type }
    , m_has_index_buffer { false }
    , m_vao   { }
{
    fill_vao( m_vao, vertices, vertex_format );

    // compute the actual size per vertex
    const auto vertex_size = compute_vertex_size( vertex_format );
    EXPECT( math::is_divisible_by( vertices.size(), vertex_size ), "Vector of vertex floats has unexpected length." );
    m_count = vertices.size() / vertex_size;
}

//----------------------------------------------------------------
Primitive3D::Primitive3D
(
    const gl::PrimitiveType             primitive_type,
    const std::vector<float>&       vertices,
    const std::vector<uint32_t>&    indices,
    const VertexFormat&             vertex_format
)
    : m_type  { primitive_type }
    , m_has_index_buffer { true }
    , m_vao   { }
{
    fill_vao( m_vao, vertices, indices, vertex_format );

    // compute the actual size per vertex
    const auto vertex_size = compute_vertex_size( vertex_format );
    EXPECT( math::is_divisible_by( vertices.size(), vertex_size ), "Vector of vertex floats has unexpected length." );
    m_count = vertices.size() / vertex_size;
}

//----------------------------------------------------------------
void Primitive3D::draw() const
{
    m_vao.bind();
    graphics::draw( *this );
}

} // namespace gl
} // namespace shake
