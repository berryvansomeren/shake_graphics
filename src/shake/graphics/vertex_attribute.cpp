#include "vertex_attribute.hpp"


#include "shake/core/contracts/contracts.hpp"
#include "shake/core/types/underlying_cast.hpp"


namespace shake {
namespace graphics {

//----------------------------------------------------------------
VertexAttribute::VertexAttribute()
    : m_is_specified    { false }
    , m_is_enabled      { false }
{ }

//----------------------------------------------------------------
void VertexAttribute::specify( Location location, Size size, uint32_t stride, uint32_t offset )
{
    m_is_specified = true;
    glVertexAttribPointer
    (
        static_cast<uint8_t>(location),
        static_cast<uint8_t>(size),
        GL_FLOAT, GL_FALSE,
        sizeof(GLfloat) * stride,
        reinterpret_cast<GLvoid*>(sizeof(GLfloat) * offset)
    );
}

//----------------------------------------------------------------
void VertexAttribute::enable( Location location )
{
    CHECK(m_is_specified, "Trying to enable VertexAttrib while it is not yet specified.");
    CHECK(!m_is_enabled, "Trying to enable VertexAttrib while it already is enabled.");
    m_is_enabled = true;
    glEnableVertexAttribArray( underlying_cast( location ) );
}

//----------------------------------------------------------------
void VertexAttribute::disable( Location location )
{
    CHECK(m_is_enabled, "Trying to disable VertexAttrib while it already is disabled.");
    m_is_enabled = false;
    glDisableVertexAttribArray( underlying_cast( location ) );
}

//----------------------------------------------------------------
void VertexAttribute::set_divisor( Location location, const uint32_t divisor )
{
     CHECK(m_is_specified, "Trying to set VertexAttrib divisor while it is not yet specified.");
     glVertexAttribDivisor( underlying_cast( location ), 1 );
}

} // namespace graphics
} // namespace shake
