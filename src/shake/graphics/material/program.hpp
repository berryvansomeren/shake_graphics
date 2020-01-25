#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <cstdint>
#include <memory>
#include <string>

#include "shake/core/macros/macro_non_copyable.hpp"
#include "shake/core/macros/macro_property.hpp"

#include "shake/graphics/gl/gl_enum.hpp"
#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/gl/gl_int.hpp"
#include "shake/graphics/material/shader.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class Program
{
public:
    Program();
    NON_COPYABLE( Program )
    Program( Program&& other );
    Program& operator=( Program&& other );
    ~Program();

private:
    PROPERTY_R( gl::ProgramId, id );
};

//----------------------------------------------------------------
Program make_program( const Shader& vertex_shader, const Shader& fragment_shader );

} // namespace graphics
} // namespace shake

#endif // PROGRAM_HPP
