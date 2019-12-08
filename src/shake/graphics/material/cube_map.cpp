#include "cube_map.hpp"

#include "shake/core/type_traits/underlying_cast.hpp"


namespace shake {
namespace graphics {

//----------------------------------------------------------------
CubeMap::CubeMap
(
    const ImageData&            image_data,
    const gl::TextureFormat     texture_format,
    const gl::Filter            filter
)
    : m_id { gl::gen_texture() }
{
    

    gl::texture_parameter( m_id, gl::TextureWrap::ClampToEdge );
    gl::texture_parameter( m_id, filter );

    // Load and generate the texture on gpu
    //for ( GLuint cube_face_index = 0; cube_face_index < n_cube_faces; ++cube_face_index )
    //{
    //    const auto& image_info = image_data.at( cube_face_index );

    //    //glTexImage2D
    //    //(
    //    //    GL_TEXTURE_CUBE_MAP_POSITIVE_X + cube_face_index,
    //    //    0,
    //    //    gl_image_format,
    //    //    static_cast<GLsizei>( image_info.width ),
    //    //    static_cast<GLsizei>( image_info.height ),
    //    //    0,
    //    //    gl_texture_format,
    //    //    GL_UNSIGNED_BYTE,
    //    //    image_info.ptr
    //    //);
    //}
}

//----------------------------------------------------------------
CubeMap::~CubeMap()
{
    gl::delete_texture( m_id );
}

//----------------------------------------------------------------
void CubeMap::bind( gl::TextureUnitIndex texture_unit ) const
{
    gl::active_texture( texture_unit );
    gl::bind_texture( gl::TextureTarget::CubeMap, m_id );
}

} // namespace graphics
} // namespace shake
