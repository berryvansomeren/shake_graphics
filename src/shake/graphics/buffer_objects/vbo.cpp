#include "vbo.hpp"

#include <glad/glad.h>

#include "shake/core/contracts/contracts.hpp"

#include "shake/graphics/gl.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
Vbo::Vbo()
{
    glGenBuffers(1, &m_id);
}

//----------------------------------------------------------------
Vbo::~Vbo()
{
    glDeleteBuffers(1, &m_id);
}

//----------------------------------------------------------------
void Vbo::bind() const
{
    gl::set_current_vbo_id(m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

//----------------------------------------------------------------
void Vbo::unbind() const
{
    CHECK_EQ(m_id, gl::get_current_vbo_id(), "Trying to unbind a VBO while it is not currently bound.");
    gl::set_current_vbo_id(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//----------------------------------------------------------------
void Vbo::set_data(const std::vector<float>& data) const
{
    CHECK_EQ(m_id, gl::get_current_vbo_id(), "Trying to set VBO data while it is not currently bound.");
    glBufferData(GL_ARRAY_BUFFER, sizeof(data[0]) * data.size(), data.data(), GL_STATIC_DRAW);
}

} // namespace graphics
} // namespace shake
