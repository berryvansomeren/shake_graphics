#ifndef BINDING_POINT_HPP
#define BINDING_POINT_HPP

#include "shake/graphics/buffer_objects/vbo.hpp"
#include "shake/graphics/buffer_objects/vertex_format.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
/*
    A Vao has multiple binding points (usually 16+)
    These binding points are used to specify both a Vbo, 
    and all the vertex attribute formats to read from the buffer. 
    We combine the vertex attribute formats in what we call a vertex format. 
    The binding points allow you to separate data from format specification. 
    This class does not actually represent the actual binding point, 
    but rather a collection of things you bind to a binding point.
*/

//----------------------------------------------------------------
struct BindingPointSpecification
{
    BindingPointSpecification
    (
        const VertexFormat& vertex_format,
        const std::shared_ptr<Vbo> vbo
    )
    : m_buffer_format { vertex_format }
    , m_buffer { vbo }
    { } 

    PROPERTY_R( VertexFormat,           buffer_format   )
    PROPERTY_R( std::shared_ptr<Vbo>,   buffer          )
};

} // namespace graphics
} // namespace shake

#endif // BINDING_POINT_HPP
