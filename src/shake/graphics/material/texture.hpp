#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <memory>
#include <cstdint>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/macros/macro_non_copyable.hpp"
//#include "shake/io/path.hpp"
#include "shake/graphics/gl/gl.hpp"
#include "shake/graphics/material/texture_parameters.hpp"

namespace shake {
namespace graphics {

class Texture
{
public:
    Texture
    (
        const uint8_t*              image_ptr,
        const uint32_t              width,
        const uint32_t              height,
        const gl::TextureFormat     texture_format,
        const gl::Filter            filter
    );

    ~Texture();

    NON_COPYABLE( Texture )

    inline int  get_width   ()  const   { return m_width;   }
    inline int  get_height  ()  const   { return m_height;  }

    void bind   ( gl::TextureUnitIndex texture_unit_id ) const;

private:
    std::uint32_t	m_width;
    std::uint32_t	m_height;
    gl::TextureId   m_id;
};

} // namespace graphics
} // namespace shake

#endif // TEXTURE_HPP
