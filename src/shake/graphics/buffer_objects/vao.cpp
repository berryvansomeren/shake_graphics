#include "vao.hpp"

#include <glad/glad.h>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/type_traits/underlying_cast.hpp"

#include "shake/graphics/buffer_objects/ebo.hpp"
#include "shake/graphics/buffer_objects/vao.hpp"
#include "shake/graphics/buffer_objects/vbo.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
Vao::Vao()
: m_id { gl::gen_vertex_array() }
{ }

//----------------------------------------------------------------
Vao::~Vao()
{
    gl::delete_vertex_array( m_id );
}

//----------------------------------------------------------------
void Vao::bind() const
{
    gl::bind_vertex_array( m_id );
}

//----------------------------------------------------------------
void Vao::specify_enable_vertex_format( const VertexFormat& vertex_format )
{
    uint32_t stride = 0;
    for ( const auto& element : vertex_format )
    {
        stride += static_cast<uint32_t>( shake::underlying_cast( element.size ) );
    }

    uint32_t offset = 0;
    for ( const auto& element : vertex_format )
    {
        specify_vertex_attrib ( element.location, element.size, stride, offset );
        enable_vertex_attrib  ( element.location );
        offset += static_cast<uint32_t>( shake::underlying_cast( element.size ) );
    }
}

//----------------------------------------------------------------
void Vao::specify_enable_vertex_format_instanced( const VertexFormat& vertex_format )
{
    specify_enable_vertex_format( vertex_format );

    for ( const auto& element : vertex_format )
    {
        set_vertex_attrib_divisor( element.location, 1 );
    }
}

//----------------------------------------------------------------
void Vao::specify_vertex_attrib
(
    gl::VertexAttributeIndex   location,
    VertexAttribute::Size       size,
    uint32_t                    stride,
    uint32_t                    offset
)
{
    //CHECK_EQ(m_id, gl::get_current_vao_id(), "Trying to specify a vertex attribute while the vao is not currently bound.");
    m_vertex_attributes[ *location ].specify(location, size, stride, offset);
}

//----------------------------------------------------------------
void Vao::enable_vertex_attrib( gl::VertexAttributeIndex location)
{
    //CHECK_EQ(m_id, gl::get_current_vao_id(), "Trying to enable a vertex attribute while the vao is not currently bound.");
    m_vertex_attributes[ *location ].enable( location );
}

//----------------------------------------------------------------
void Vao::disable_vertex_attrib( gl::VertexAttributeIndex location)
{
    //CHECK_EQ(m_id, gl::get_current_vao_id(), "Trying to disable a vertex attribute while the vao is not currently bound.");
    m_vertex_attributes[ *location ].disable( location );
}

//----------------------------------------------------------------
void Vao::set_vertex_attrib_divisor( gl::VertexAttributeIndex location, const uint32_t divisor )
{
    //CHECK_EQ(m_id, gl::get_current_vao_id(), "Trying to disable a vertex attribute while the vao is not currently bound.");
    m_vertex_attributes[ *location ].set_divisor( location, divisor );
}

//----------------------------------------------------------------
void fill_vao
(
          Vao&                      vao,
    const std::vector<float>&       vertices,
    const VertexFormat&             vertex_format
)
{
    Vbo vbo {};
    vao.bind();
    vbo.bind();
    vbo.set_data( vertices );
    vao.specify_enable_vertex_format( vertex_format );
}

//----------------------------------------------------------------
void fill_vao
(
          Vao&                      vao,
    const std::vector<float>&       vertices,
    const std::vector<uint32_t>&    indices,
    const VertexFormat&             vertex_format
)
{
    Vbo vbo {};
    Ebo ebo {};
    vao.bind();
    vbo.bind();
    vbo.set_data( vertices );
    ebo.bind();
    ebo.set_data( indices );
    vao.specify_enable_vertex_format( vertex_format );
}

} // namespace graphics
} // namespace shake
