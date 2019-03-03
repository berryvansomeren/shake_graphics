#ifndef VBO_HPP
#define VBO_HPP

#include <memory>
#include <cstdint>
#include <vector>

#include "shake/core/types/macro_non_copyable.hpp"

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
    void unbind() const;

    void set_data(const std::vector<float>&     data) const;

private:
    uint32_t m_id;
};

} // namespace graphics
} // namespace shake

#endif // VBO_HPP
