#include "texture.hpp"

#include <string>
#include <cassert>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/type_traits/underlying_cast.hpp"
#include "shake/core/log.hpp"

//#include "shake/io/file.hpp"

#include "shake/graphics/gl/gl.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
Texture::Texture
(
    const uint8_t*          image_ptr,
    const uint32_t          width,
    const uint32_t          height,
    const gl::TextureFormat texture_format,
    const gl::Filter        filter
)
    : m_id      { gl::gen_texture() }
    , m_width   { width     }
    , m_height  { height    } 
{
    gl::bind_texture( gl::TextureTarget::_2D, m_id );
    gl::texture_parameter( m_id, gl::TextureWrap::ClampToEdge );
    gl::texture_parameter( m_id, filter );

    // gl::texture_storage_2d()
    // gl::texture_sub_image_2d()
}

//----------------------------------------------------------------
Texture::~Texture()
{
    gl::delete_texture( m_id );
}

//----------------------------------------------------------------
void Texture::bind( gl::TextureUnitIndex texture_unit ) const
{
    gl::active_texture( texture_unit );
    gl::bind_texture( gl::TextureTarget::_2D, m_id );
}

} // namespace graphics
} // namespace shake
