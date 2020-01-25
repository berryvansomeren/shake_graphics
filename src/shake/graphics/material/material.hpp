#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>

#include "shake/core/std/map.hpp"
#include "shake/core/macros/macro_property.hpp"
#include "shake/graphics/material/uniform.hpp"
#include "shake/graphics/material/uniform_map.hpp"
#include "shake/graphics/material/program.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class Material
{
public:
    //----------------------------------------------------------------
    Material( const std::shared_ptr<Program>& program )
        : m_program { program }
        , m_uniforms { get_uniform_map( program->get_id() ) }
    { }

    //----------------------------------------------------------------
    inline bool has_uniform( const std::string& uniform_name ) const
    {
        return map::has( m_uniforms, uniform_name );
    }

    //----------------------------------------------------------------
    template< typename Uniform_T >
    void set_uniform( const std::string& uniform_name, Uniform_T uniform ) const
    {
        const auto shader_id = m_program->get_id();
        const auto uniform_location = m_uniforms.at( uniform_name );
        gl::program_uniform( shader_id, uniform_location, uniform );
    }

    //----------------------------------------------------------------
    template< typename Uniform_T >
    bool try_set_uniform( const std::string& uniform_name, Uniform_T uniform ) const
    {
        const auto uniform_present = has_uniform( uniform_name );
        if ( uniform_present ) { set_uniform( uniform_name, uniform ); }
        return uniform_present;
    }

    //----------------------------------------------------------------
    inline void bind() const
    {
        gl::use_program( m_program->get_id() );
    }

private:
    UniformMap                  m_uniforms;
    std::shared_ptr<Program>    m_program;
};

} // namespace graphics
} // namespace shake

#endif // MATERIAL_HPP
