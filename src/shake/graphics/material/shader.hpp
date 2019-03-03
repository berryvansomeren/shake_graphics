#ifndef SHADER_HPP
#define SHADER_HPP

#include <cstdint>
#include <memory>
#include <string>

#include "shake/core/types/macro_non_copyable.hpp"

#include "shake/graphics/material/shader_type.hpp"

namespace shake {
namespace graphics {

class Shader
{
public:
    using Ptr = std::shared_ptr<Shader>;

public:
    Shader();
    ~Shader();

    NON_COPYABLE( Shader )

    inline void     bind()              const;
    inline void     unbind()            const;
    inline uint32_t get_program_id()    const;

    // attach a shader to the current shader program
    void attach(const std::string &source, const ShaderType shader_type );

    // link all attached shaders together into a program
    void link();

    // used for debugging (expensive)
    bool is_valid();

    // create a basic shader program with just a vertex and a fragment shader
    static std::unique_ptr<Shader> create_basic(const std::string &vertex_shader_source, const std::string &fragment_shader_source);

    bool has_uniform_location( const std::string& uniform_name ) const;
    int32_t get_uniform_location( const std::string& uniform_name ) const;

    template<typename T>
    inline void set_uniform(const int32_t uniform_location, const T& value);

    template<typename T>
    inline void set_uniform(const std::string& uniform_name, const T& value);

private:
    // helper for creating different types of shaders
    uint32_t create( const ShaderType& shader_type );

private:
    uint32_t m_id;
};

} // namespace graphics
} // namespace shake

#include "shader.inl"

#endif // SHADER_HPP
