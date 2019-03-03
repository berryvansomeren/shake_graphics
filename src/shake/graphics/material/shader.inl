#include "shader.hpp"

#include <glad/glad.h>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/math/math.hpp"
#include "shake/graphics/gl.hpp"

namespace shake {
namespace graphics {

namespace { // anonymous

//----------------------------------------------------------------
template<typename T>
inline void set_uniform_impl(const int32_t uniform_location, const T& value);

template<> inline
void set_uniform_impl(const int32_t uniform_location, const glm::mat4& value)
{
    glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(value));
}

template<> inline
void set_uniform_impl(const int32_t uniform_location, const glm::vec3& value)
{
    glUniform3f(uniform_location, value.x, value.y, value.z);
}

template<> inline
void set_uniform_impl(const int32_t uniform_location, const glm::vec2& value)
{
    glUniform2f(uniform_location, value.x, value.y);
}

template<> inline
void set_uniform_impl(const int32_t uniform_location, const float& value)
{
    glUniform1f(uniform_location, value);
}

template<> inline
void set_uniform_impl(const int32_t uniform_location, const int32_t& value)
{
    glUniform1i(uniform_location, value);
}

} // namespace anonymous

//----------------------------------------------------------------
inline void Shader::bind() const
{
    CHECK_NE(m_id, gl::get_current_shader_id(), "Trying to bind a shader while it is already bound.");
    gl::set_current_shader_id(m_id);
    glUseProgram(m_id);
}

//----------------------------------------------------------------
inline void Shader::unbind() const
{
    CHECK_EQ(m_id, gl::get_current_shader_id(), "Trying to unbind a shader while it is not currently bound.");
    gl::set_current_shader_id(0);
    glUseProgram(0);
}

//----------------------------------------------------------------
inline uint32_t Shader::get_program_id() const
{
    return m_id;
}

//----------------------------------------------------------------
inline bool Shader::has_uniform_location( const std::string& uniform_name ) const
{
    GLint uniform_location { glGetUniformLocation(m_id, uniform_name.c_str()) };
    return uniform_location >= 0;
}

//----------------------------------------------------------------
inline int32_t Shader::get_uniform_location(const std::string& uniform_name) const
{
    GLint uniform_location { glGetUniformLocation(m_id, uniform_name.c_str()) };
    CHECK_GE(uniform_location, 0, "Could not find uniform " + uniform_name);
    return uniform_location;
}

//----------------------------------------------------------------
template<typename T> inline
void Shader::set_uniform(const std::string& uniform_name, const T& value)
{
    CHECK_EQ(m_id, gl::get_current_shader_id(), "Trying to set uniform while shader is not currently bound.");
    set_uniform(get_uniform_location(uniform_name), value);
}

template<typename T>
inline void Shader::set_uniform(const int32_t uniform_location, const T& value)
{
    CHECK_EQ(m_id, gl::get_current_shader_id(), "Trying to set uniform while shader is not currently bound.");
    set_uniform_impl(uniform_location, value);
}

} // namespace graphics
} // namespace shake
