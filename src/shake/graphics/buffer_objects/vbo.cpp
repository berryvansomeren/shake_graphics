#include "vbo.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
Vbo::Vbo()
: m_id { gl::gen_buffer() }
{ }

//----------------------------------------------------------------
Vbo::~Vbo()
{
    gl::delete_buffer( m_id );
}

//----------------------------------------------------------------
void Vbo::bind() const
{
    gl::bind_buffer( gl::BufferTarget::ArrayBuffer, m_id );
}

//----------------------------------------------------------------
void Vbo::set_data(const std::vector<float>& data) const
{
    const auto size = gl::SizeI { sizeof( data[ 0 ] ) * data.size() };
    gl::buffer_data( m_id, size, data.data(), gl::Usage::StaticDraw );
}

} // namespace graphics
} // namespace shake
