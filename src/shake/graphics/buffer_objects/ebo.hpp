#ifndef EBO_HPP
#define EBO_HPP

#include <memory>
#include <cstdint>
#include <vector>

#include "shake/core/types/macro_non_copyable.hpp"

namespace shake {
namespace graphics {

class Ebo
{
public:
    using Ptr = std::shared_ptr<Ebo>;

public:
    Ebo();
    ~Ebo();

    NON_COPYABLE( Ebo )

    void bind() const;
    void unbind() const;

    void set_data(const std::vector<uint32_t> &data) const;

private:
    uint32_t m_id;
};

} // namespace graphics
} // namespace shake

#endif // EBO_HPP
