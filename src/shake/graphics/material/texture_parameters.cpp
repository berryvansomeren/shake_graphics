//#include "texture_parameters.hpp"
//
//#include <glad/glad.h>
//
//#include "shake/core/data_structures/map.hpp"
//
//namespace shake {
//namespace graphics {
//
////----------------------------------------------------------------
//ImageFormat string_to_image_format( const std::string s )
//{
//    return Map<std::string, ImageFormat>
//    {
//        { "r",      ImageFormat::R      }, 
//        { "rgb",    ImageFormat::RGB    },
//        { "rgba",   ImageFormat::RGBA   }
//    }.at( s );
//}
//
////----------------------------------------------------------------
//GLintAlias image_format_to_gl( const ImageFormat image_format )
//{
//    return Map< ImageFormat, GLintAlias >
//    {
//        { ImageFormat::R,       GL_RED  }, 
//        { ImageFormat::RGB,     GL_RGB  },
//        { ImageFormat::RGBA,    GL_RGBA }
//    }.at( image_format );
//}
//
////----------------------------------------------------------------
//TextureFormat string_to_texture_format( const std::string string )
//{
//         if ( string == "r"     ) { return TextureFormat::R;    }
//    else if ( string == "rgb"   ) { return TextureFormat::RGB;  }
//    else if ( string == "rgba"  ) { return TextureFormat::RGBA; }
//    else
//    {
//       CHECK_FAIL( "Did not recognise texture format as string." );
//    }
//    return TextureFormat::R;
//}
//
////----------------------------------------------------------------
//GLenum texture_format_to_gl( const TextureFormat texture_format )
//{
//    switch ( texture_format )
//    {
//    case TextureFormat::R       : return GL_RED;    break;
//    case TextureFormat::RGB     : return GL_RGB;    break;
//    case TextureFormat::RGBA    : return GL_RGBA;   break;
//    default:
//        CHECK_FAIL( "Did not recognise texture format." );
//        break;
//    }
//    return GL_RED;
//}
//
////----------------------------------------------------------------
//InterpolationMode string_to_interpolation_mode( const std::string& string )
//{
//         if ( string == "linear"  ) { return InterpolationMode::Linear;  }
//    else if ( string == "nearest" ) { return InterpolationMode::Nearest; }
//    else
//    {
//        CHECK_FAIL( "Did not recognise interpolation mode as string" );
//    }
//    return InterpolationMode::Linear;
//}
//
////----------------------------------------------------------------
//GLint interpolation_mode_to_gl( const InterpolationMode interpolation_mode )
//{
//    switch ( interpolation_mode )
//    {
//    case InterpolationMode::Nearest : return GL_NEAREST;    break;
//    case InterpolationMode::Linear  : return GL_LINEAR;     break;
//    default:
//        CHECK_FAIL( "Did not recognise texture interpolation mode" );
//        break;
//    }
//    return GL_NEAREST;
//}
//
////----------------------------------------------------------------
//GLenum index_to_texture_unit(const uint8_t index)
//{
//    return GL_TEXTURE0 + index;
//}
//
//} // namespace graphics
//} // namespace shake
