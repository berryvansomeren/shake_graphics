#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <memory>
#include <cstdint>

#include <glad/glad.h>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/types/macro_non_copyable.hpp"
//#include "shake/io/path.hpp"
#include "shake/graphics/material/texture_parameters.hpp"

namespace shake {
namespace graphics {

class Texture
{
public:
    using Ptr = std::shared_ptr<Texture>;

public:
    Texture
    (
        const uint8_t*          image_ptr,
        const uint32_t          width,
        const uint32_t          height,
        const ImageFormat       image_format,
        const TextureFormat     texture_format,
        const InterpolationMode interpolation_mode,
        const bool              generate_mip_maps
    );

    ~Texture();

    NON_COPYABLE( Texture )

    inline int  get_width   ()  const   { return m_width;   }
    inline int  get_height  ()  const   { return m_height;  }

    void bind   ( TextureUnit texture_unit_id ) const;
    void unbind ()                          const;

private:
    std::uint32_t	m_width;
    std::uint32_t	m_height;
    std::uint32_t   m_id;
};

} // namespace graphics
} // namespace shake

#endif // TEXTURE_HPP
