#ifndef VBO_HPP
#define VBO_HPP

#include <memory>
#include <cstdint>
#include <vector>

#include "shake/core/macros/macro_non_copyable.hpp"
#include "shake/core/macros/macro_property.hpp"

#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/gl/gl_int.hpp"
#include "shake/graphics/buffer_objects/vertex_format.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
/*
    Vertex Buffer Objects store vertex data.

    While in OpenGL there is the concept of "separate attribute format",
    which enables us to separately specify the format of a vertex attribute from the source buffer,
    we don't really care about that for now. 
    We always use a single buffer for all our verte data, 
    and store the format with the buffer. 

    This can take different types and shapes,
    so we could use some kind of polymorphism to store this data inside the class. 
    However, since we only push the data to the gpu, and then only need to VBO id,
    our vbo classes only manages this id. 
    Passing the data to the gpu is done by the helper functions underneath. 
*/

//----------------------------------------------------------------
class Vbo
{
public:
    Vbo();
    NON_COPYABLE( Vbo )
    Vbo( Vbo&& other );
    Vbo& operator=( Vbo&& other );
    ~Vbo();

private:
    PROPERTY_R( gl::VboId, id )
};

//----------------------------------------------------------------
Vbo make_vbo( const std::vector<float>& vertex_data );

} // namespace graphics
} // namespace shake

#endif // VBO_HPP