#ifndef VAO_HPP
#define VAO_HPP

#include <memory>
#include <vector>

#include "shake/core/macros/macro_non_copyable.hpp"
#include "shake/core/macros/macro_property.hpp"

#include "shake/graphics/gl/gl_int.hpp"
#include "shake/graphics/buffer_objects/binding_point_specification.hpp"
#include "shake/graphics/buffer_objects/vbo.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
/*
    Vertex Array Objects store all data needed to supply vertex data.
    While the VBO stores only a single data buffer,
    multiple can be bound to a VAO, 
    and a VAO also keeps track of their attributes and corresponding formats. 

    This can take different types and shapes,
    so we could use some kind of polymorphism to store this data inside the class. 
    However, since we only push the data to the gpu, and then only need to VBO id,
    our vbo classes only manages this id. 
    Passing the data to the gpu is done by the helper functions underneath. 
*/

//----------------------------------------------------------------
class Vao
{
public:
    // rule of five
    Vao();
    NON_COPYABLE( Vao )
    Vao( Vao&& other );
    Vao& operator=( Vao&& other );
    ~Vao();

    void bind( const std::shared_ptr<Vbo>& vbo );

private:
    PROPERTY_R( gl::VaoId, id )

    std::vector<std::shared_ptr<Vbo>> m_bound_buffers;
};

//----------------------------------------------------------------
Vao make_vao
(
    const BindingPointSpecification& binding_point_specification
);

} // namespace graphics
} // namespace shake

#endif // VAO_HPP
