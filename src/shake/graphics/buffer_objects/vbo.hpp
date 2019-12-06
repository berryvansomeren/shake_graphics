#ifndef VBO_HPP
#define VBO_HPP

#include <memory>
#include <cstdint>
#include <vector>

#include "shake/core/macros/macro_non_copyable.hpp"

#include "shake/graphics/gl/gl.hpp"

namespace shake {
namespace graphics {

class Vbo
{
public:
    using Ptr = std::shared_ptr<Vbo>;

public:
    Vbo();
    ~Vbo();

    NON_COPYABLE( Vbo )

    void bind() const;

    void set_data(const std::vector<float>&     data) const;

private:
    gl::BufferId m_id;
};

} // namespace graphics
} // namespace shake

#endif // VBO_HPP
