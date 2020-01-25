#include "vbo.hpp"

namespace shake {
namespace graphics {

namespace { // anonymous

//----------------------------------------------------------------
const auto invalid_vbo_id = gl::VboId { std::numeric_limits<gl::VboId::value_type>::max() };

//----------------------------------------------------------------
bool is_valid( const gl::VboId& id )
{
    return *id < *invalid_vbo_id;
}

//----------------------------------------------------------------
template< typename Vector_T >
gl::Size get_vertex_data_size( const Vector_T& vertex_data )
{
    const auto vertex_data_size_in_bytes = gl::Size 
    { 
        static_cast< gl::Size::value_type >
        ( 
            sizeof( Vector_T::value_type ) * vertex_data.size()
        )
    };
    return vertex_data_size_in_bytes;
}

} // anonymous

//----------------------------------------------------------------
Vbo::Vbo() 
    : m_id { *gl::create_buffer() } 
{ }

//----------------------------------------------------------------
Vbo::Vbo( Vbo&& other )
    : m_id { other.m_id }
{
    other.m_id = invalid_vbo_id;
}

//----------------------------------------------------------------
Vbo& Vbo::operator=( Vbo&& other )
{
    m_id = other.get_id();
    other.m_id = invalid_vbo_id;
    return *this;
}

//----------------------------------------------------------------
Vbo::~Vbo() 
{ 
    // Maximum possible value for vbo id is used to indicate it shouldn't be deleted,
    // because another object took ownership (via move).
    // This approach avoids the use of an extra bool or std::optional,
    // which would introduce a lot more overhead ( especially memory due to padding ).
    if ( is_valid( m_id ) )
    {
        gl::delete_buffer( gl::BufferId { *m_id } ); 
    }
}

//----------------------------------------------------------------
//void Vbo::bind( const gl::VertexBufferBindingIndex binding_index ) const
//{
//    gl::bind_buffer( gl::BufferTarget::ArrayBuffer, m_id );
//}

////----------------------------------------------------------------
//void Vbo::set_data( const std::vector<float>& data ) const
//{
//    const auto size = gl::Size { sizeof( data[ 0 ] ) * data.size() };
//    gl::buffer_data( m_id, size, data.data(), gl::Usage::StaticDraw );
//}

//----------------------------------------------------------------
//----------------------------------------------------------------
Vbo make_vbo( const std::vector<float>& vertex_data )
{
    auto vbo = Vbo { };
    gl::named_buffer_data
    ( 
        gl::BufferId { *vbo.get_id() }, 
        get_vertex_data_size( vertex_data ), 
        vertex_data.data(), 
        gl::Usage::StaticDraw 
    );
    return vbo;
}

} // namespace graphics
} // namespace shake
