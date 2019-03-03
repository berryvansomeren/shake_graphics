#include "cube_map.hpp"

#include "shake/core/types/underlying_cast.hpp"
#include "shake/graphics/gl.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
CubeMap::CubeMap
(
    const ImageData&        image_data,
    const ImageFormat       image_format,
    const TextureFormat     texture_format,
    const InterpolationMode interpolation_mode,
    const bool              generate_mip_maps
)
{
    // create and activate teture buffer
    glGenTextures( 1, &m_id );
    glBindTexture( GL_TEXTURE_CUBE_MAP, m_id );

    // Set the texture wrapping parameters
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );

    // Set texture filtering parameters
    const auto gl_interpolation_mode { interpolation_mode_to_gl( interpolation_mode ) };
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, gl_interpolation_mode );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, gl_interpolation_mode );

    // Parse format parameters
    const auto gl_image_format      = image_format_to_gl    ( image_format   );
    const auto gl_texture_format    = texture_format_to_gl  ( texture_format );

    // Load and generate the texture on gpu
    for ( GLuint cube_face_index = 0; cube_face_index < n_cube_faces; ++cube_face_index )
    {
        const auto& image_info = image_data[ cube_face_index ];

        glTexImage2D
        (
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + cube_face_index,
            0,
            gl_image_format,
            static_cast<GLsizei>( image_info.width ),
            static_cast<GLsizei>( image_info.height ),
            0,
            gl_texture_format,
            GL_UNSIGNED_BYTE,
            image_info.ptr
        );
    }

    // Generate mip maps if required
    if( generate_mip_maps )
    {
        glGenerateMipmap( GL_TEXTURE_CUBE_MAP);
    }

    // Unbind texture when done, so we won't accidentily mess up our texture.
    unbind();
}

//----------------------------------------------------------------
CubeMap::~CubeMap()
{
    glDeleteTextures( 1, &m_id );
}

//----------------------------------------------------------------
void CubeMap::bind( TextureUnit texture_unit ) const
{
    //core::log_if_eq(m_id, gl_context::get_current_texture_id(texture_unit_index), "Trying to bind a texture to a unit it is already bound to.");
    const auto texture_unit_index = underlying_cast( texture_unit );
    gl::set_current_texture_id( texture_unit_index, m_id );
    glActiveTexture( index_to_texture_unit( texture_unit_index ) );
    glBindTexture( GL_TEXTURE_CUBE_MAP, m_id );
}

//----------------------------------------------------------------
void CubeMap::unbind() const
{
    glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
}

} // namespace graphics
} // namespace shake
