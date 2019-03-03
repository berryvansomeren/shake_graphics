#include "texture.hpp"

#include <string>
#include <cassert>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/log.hpp"

//#include "shake/io/file.hpp"

#include "shake/graphics/gl.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
Texture::Texture
(
    const uint8_t*          image_ptr,
    const uint32_t          width,
    const uint32_t          height,
    const ImageFormat       image_format,
    const TextureFormat     texture_format,
    const InterpolationMode interpolation_mode,
    const bool              generate_mip_maps
)
    : m_width   { width     }
    , m_height  { height    }
{
    // Create and activate teture buffer
    glGenTextures( 1, &m_id );
    glBindTexture( GL_TEXTURE_2D, m_id );

    // Set the texture wrapping parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    // Set texture filtering parameters
    const auto gl_interpolation_mode { interpolation_mode_to_gl( interpolation_mode ) };
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_interpolation_mode );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_interpolation_mode );

    // Parse format parameters
    const auto gl_image_format      { image_format_to_gl    ( image_format   ) };
    const auto gl_texture_format    { texture_format_to_gl  ( texture_format ) };

    // load and generate the texture on gpu
    glTexImage2D
    (
        GL_TEXTURE_2D,
        0,
        gl_image_format,
        static_cast<GLsizei>( m_width ),
        static_cast<GLsizei>( m_height ),
        0,
        gl_texture_format,
        GL_UNSIGNED_BYTE,
        image_ptr
    );

    // Generate mip maps if required
    if( generate_mip_maps )
    {
        glGenerateMipmap( GL_TEXTURE_2D);
    }

    // Unbind texture when done, so we won't accidentily mess up our texture.
    unbind();
}

//----------------------------------------------------------------
Texture::~Texture()
{
    glDeleteTextures( 1, &m_id );
}

//----------------------------------------------------------------
void Texture::bind( TextureUnit texture_unit ) const
{
    //core::log_if_eq(m_id, gl_context::get_current_texture_id(texture_unit_index), "Trying to bind a texture to a unit it is already bound to.");
    const auto texture_unit_index = underlying_cast( texture_unit );
    gl::set_current_texture_id( texture_unit_index, m_id );
    glActiveTexture( index_to_texture_unit( texture_unit_index ) );
    glBindTexture(GL_TEXTURE_2D, m_id);
}

//----------------------------------------------------------------
void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace graphics
} // namespace shake
