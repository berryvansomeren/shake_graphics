#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <cstdint>
#include <memory>
#include <string>

#include "shake/core/macros/macro_non_copyable.hpp"
#include "shake/core/macros/property.hpp"

#include "shake/graphics/gl/gl_enum.hpp"
#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/gl/gl_int.hpp"

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

    

    void     bind()              const;
    void     unbind()            const;

    // attach a shader to the current shader program
    void attach(const std::string &source, const gl::ShaderType shader_type );

    // link all attached shaders together into a program
    void link();

    // used for debugging (expensive)
    bool is_valid();

    // create a basic shader program with just a vertex and a fragment shader
    static std::unique_ptr<Program> create_basic(const std::string &vertex_shader_source, const std::string &fragment_shader_source);

    bool has_uniform( const std::string& uniform_name ) const;
    gl::UniformLocation get_uniform_location( const std::string& uniform_name ) const;

    //----------------------------------------------------------------
    template<typename T>
    void set_uniform(const std::string& uniform_name, const T& value)
    {
        /*CHECK_EQ(m_id, gl::get_current_shader_id(), "Trying to set uniform while shader is not currently bound.");*/
        gl::set_uniform( get_uniform_location(uniform_name), value);
    }

    template<typename T>
    void set_uniform(const gl::UniformLocation uniform_location, const T& value)
    {
       /* CHECK_EQ(m_id, gl::get_current_shader_id(), "Trying to set uniform while shader is not currently bound.");*/
        gl::set_uniform( uniform_location, value);
    }

    template<typename T>
    void try_set_uniform( const std::string& uniform_name, const T& value )
    {
        /*CHECK_EQ(m_id, gl::get_current_shader_id(), "Trying to set uniform while shader is not currently bound.");*/
        if ( has_uniform( uniform_name ) )
        {
            set_uniform( uniform_name, value );
        }
    }

private:
    PROPERTY_R( gl::ProgramId, id );
};

} // namespace graphics
} // namespace shake

#endif // PROGRAM_HPP
