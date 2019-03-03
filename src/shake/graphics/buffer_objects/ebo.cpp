#include "ebo.hpp"

#include <glad/glad.h>

#include "shake/core/contracts/contracts.hpp"

#include "shake/graphics/gl.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
Ebo::Ebo()
{
    glGenBuffers( 1, &m_id);
}

//----------------------------------------------------------------
Ebo::~Ebo()
{
    glDeleteBuffers( 1, &m_id );
}

//----------------------------------------------------------------
void Ebo::bind() const
{
    gl::set_current_ebo_id(m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

//----------------------------------------------------------------
void Ebo::unbind() const
{
    CHECK_EQ(m_id, gl::get_current_ebo_id(), "Trying to unbind an EBO while it is not currently bound.");
    gl::set_current_ebo_id(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//----------------------------------------------------------------
void Ebo::set_data(const std::vector<uint32_t>& data) const
{
    CHECK_EQ(m_id, gl::get_current_ebo_id(), "Trying to set EBO data while it is not currently bound.");
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data[0]) * data.size(), data.data(), GL_STATIC_DRAW);
}

} // namespace graphics
} // namespace shake
