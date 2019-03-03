#ifndef A_MATERIAL_HPP
#define A_MATERIAL_HPP

#include <memory>
#include <vector>

#include "shake/core/data_structures/map.hpp"
#include "shake/core/types/macro_property.hpp"
#include "shake/graphics/material/uniform.hpp"
#include "shake/graphics/material/shader.hpp"

namespace shake {
namespace graphics {

class Material
{
public:
    using Ptr = std::shared_ptr<Material>;

public:

    Material( const Shader::Ptr& shader )
        : m_shader { shader }
    { }

    Material& set_uniform( const std::string& name, AUniform::Ptr uniform )
    {
        // This replaces the element if it was already present in the map
        const auto uniform_location = m_shader->get_uniform_location( name );
        m_uniforms[ name ] = UniformSpecification{ uniform_location, std::move( uniform ) };
        return (*this);
    }

    // It feels a bit backward to call the bind function with so many arguments
    // But the goal is to present a clean interface for creating uniforms,
    // where you only need to specify the value of the uniform.
    // The bind() function is supposed to only be called from here.
    void bind() const
    {
        m_shader->bind();

        for ( const auto& uniform_specification : m_uniforms )
        {
            const auto& uniform = uniform_specification.second;
            uniform.value->bind( m_shader, uniform.location );
        }
    }

    void unbind() const
    {
        m_shader->unbind();
    }

private:
    struct UniformSpecification
    {
        int32_t         location;
        AUniform::Ptr   value;
    };

    using UniformMap = std::unordered_map<std::string, UniformSpecification>;

private:
    PROPERTY_R( Shader::Ptr, shader )

    UniformMap m_uniforms;
};

} // namespace graphics
} // namespace shake

#endif // A_MATERIAL_HPP
