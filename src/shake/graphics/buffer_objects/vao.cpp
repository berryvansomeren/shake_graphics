#include "vao.hpp"

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/type_traits/underlying_cast.hpp"

#include "shake/graphics/buffer_objects/ebo.hpp"
#include "shake/graphics/buffer_objects/vao.hpp"
#include "shake/graphics/buffer_objects/vbo.hpp"

namespace shake {
namespace graphics {

namespace { // anonymous

//----------------------------------------------------------------
inline void bind_vertex_format( const gl::VaoId id, const gl::BindingIndex binding_index, const VertexFormat& vertex_format )
{
    for ( const auto attribute_format : vertex_format )
    {
        // enable
        gl::enable_vertex_array_attrib( id, attribute_format.attribute_index );
        
        // specify
        gl::vertex_array_attrib_format
        (
            id, 
            attribute_format.attribute_index, 
            attribute_format.attribute_element_count, 
            attribute_format.attribute_type, 
            false, // normalized
            gl::Offset { *get_vertex_size_in_bytes( vertex_format ) }
        );

        // bind
        gl::vertex_array_attrib_binding( id, attribute_format.attribute_index, binding_index );
    }
}

//----------------------------------------------------------------
inline void bind_binding_point_specification
( 
    const gl::VaoId id, 
    const gl::BindingIndex binding_index, 
    const BindingPointSpecification& binding_point_specification 
)
{
    // To this specific binding point index,
    // of this specific vao,
    // we bind the following:

    // 1: the buffer format specification
    bind_vertex_format
    ( 
        id, 
        binding_index, 
        binding_point_specification.get_buffer_format() 
    );

    // 2: the vertex buffer itself
    gl::vertex_array_vertex_buffer
    ( 
        id, 
        binding_index, 
        binding_point_specification.get_buffer()->get_id(), 
        gl::Offset { 0 }, 
        get_vertex_size_in_bytes( binding_point_specification.get_buffer_format() ) 
    );
}

//----------------------------------------------------------------
const auto invalid_vbo_id = gl::VaoId { std::numeric_limits<gl::VaoId::value_type>::max() };

//----------------------------------------------------------------
bool is_valid( const gl::VaoId& id )
{
    return *id < *invalid_vbo_id;
}

} // namespace anonymous

//----------------------------------------------------------------
Vao::Vao() 
    : m_id { gl::create_vertex_array() }
{ }

//----------------------------------------------------------------
Vao::Vao( Vao&& other )
    : m_id { other.m_id }
{
    other.m_id = invalid_vbo_id;
}

//----------------------------------------------------------------
Vao& Vao::operator=( Vao&& other )
{
    m_id = other.get_id();
    other.m_id = invalid_vbo_id;
    return *this;
}

//----------------------------------------------------------------
Vao::~Vao() 
{ 
    // Maximum possible value for vao id is used to indicate it shouldn't be deleted,
    // because another object took ownership (via move).
    // This approach avoids the use of an extra bool or std::optional,
    // which would introduce a lot more overhead ( especially memory due to padding ).
    if ( is_valid( m_id ) )
    {
        gl::delete_vertex_array( m_id ); 
    }
}

//----------------------------------------------------------------
void Vao::bind( const std::shared_ptr<Vbo>& vbo )
{
    m_bound_buffers.emplace_back( vbo );
}

//----------------------------------------------------------------
Vao make_vao
(
    const BindingPointSpecification& binding_point_specification
)
{
    auto vao = Vao { };
    const auto binding_point_index = gl::BindingIndex { 0 };
    bind_binding_point_specification( vao.get_id(), binding_point_index, binding_point_specification );
    vao.bind( binding_point_specification.get_buffer() );
    return vao;
}

} // namespace graphics
} // namespace shake
