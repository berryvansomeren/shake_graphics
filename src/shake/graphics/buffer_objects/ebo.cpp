#include "ebo.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
Ebo::Ebo()
: m_id { gl::gen_buffer() }
{ }

//----------------------------------------------------------------
Ebo::~Ebo()
{
    gl::delete_buffer( m_id );
}

//----------------------------------------------------------------
void Ebo::bind() const
{
    gl::bind_buffer( gl::BufferTarget::ElementArrayBuffer, m_id );
}

//----------------------------------------------------------------
void Ebo::set_data(const std::vector<uint32_t>& data) const
{
    const auto size = gl::SizeI { sizeof( data[ 0 ] ) * data.size() };
    gl::buffer_data( m_id, size, data.data(), gl::Usage::StaticDraw );
}

} // namespace graphics
} // namespace shake
