#ifndef TEXTURE_PARAMETERS_HPP
#define TEXTURE_PARAMETERS_HPP

#include <glad/glad.h>

#include <string>

#include "shake/core/contracts/contracts.hpp"

namespace shake {
namespace graphics {

enum class TextureUnit : uint8_t
{
    Albedo = 0,
    Skybox = 1
};

enum class ImageFormat          { R, RGB, RGBA      };
enum class TextureFormat        { R, RGB, RGBA      };
enum class InterpolationMode    { Nearest, Linear   };

//----------------------------------------------------------------
inline ImageFormat string_to_image_format( const std::string string )
{
         if ( string == "r"     ) { return ImageFormat::R;     }
    else if ( string == "rgb"   ) { return ImageFormat::RGB;   }
    else if ( string == "rgba"  ) { return ImageFormat::RGBA;  }
    else
    {
        CHECK_FAIL( "Did not recognise image format as string." );
    }
    return ImageFormat::R;
}

//----------------------------------------------------------------
inline GLint image_format_to_gl( const ImageFormat image_format )
{
    switch ( image_format )
    {
    case ImageFormat::R    : return GL_RED;    break;
    case ImageFormat::RGB  : return GL_RGB;    break;
    case ImageFormat::RGBA : return GL_RGBA;   break;
    default:
        CHECK_FAIL( "Did not recognise image format." );
        break;
    }
    return GL_RED;
}

//----------------------------------------------------------------
inline TextureFormat string_to_texture_format( const std::string string )
{
         if ( string == "r"     ) { return TextureFormat::R;    }
    else if ( string == "rgb"   ) { return TextureFormat::RGB;  }
    else if ( string == "rgba"  ) { return TextureFormat::RGBA; }
    else
    {
       CHECK_FAIL( "Did not recognise texture format as string." );
    }
    return TextureFormat::R;
}

//----------------------------------------------------------------
inline GLenum texture_format_to_gl( const TextureFormat texture_format )
{
    switch ( texture_format )
    {
    case TextureFormat::R       : return GL_RED;    break;
    case TextureFormat::RGB     : return GL_RGB;    break;
    case TextureFormat::RGBA    : return GL_RGBA;   break;
    default:
        CHECK_FAIL( "Did not recognise texture format." );
        break;
    }
    return GL_RED;
}

//----------------------------------------------------------------
inline InterpolationMode string_to_interpolation_mode( const std::string& string )
{
         if ( string == "linear"  ) { return InterpolationMode::Linear;  }
    else if ( string == "nearest" ) { return InterpolationMode::Nearest; }
    else
    {
        CHECK_FAIL( "Did not recognise interpolation mode as string" );
    }
    return InterpolationMode::Linear;
}

//----------------------------------------------------------------
inline GLint interpolation_mode_to_gl( const InterpolationMode interpolation_mode )
{
    switch ( interpolation_mode )
    {
    case InterpolationMode::Nearest : return GL_NEAREST;    break;
    case InterpolationMode::Linear  : return GL_LINEAR;     break;
    default:
        CHECK_FAIL( "Did not recognise texture interpolation mode" );
        break;
    }
    return GL_NEAREST;
}

//----------------------------------------------------------------
inline GLenum index_to_texture_unit(const uint8_t index)
{
    return GL_TEXTURE0 + index;
}

} // namespace graphics
} // namespace shake

#endif // TEXTURE_PARAMETERS_HPP
