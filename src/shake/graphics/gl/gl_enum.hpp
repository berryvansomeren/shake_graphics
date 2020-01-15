#ifndef GL_ENUM_HPP
#define GL_ENUM_HPP

#include "shake/core/type_traits/underlying_cast.hpp"

#include "shake/graphics/gl/gl_int.hpp"

namespace shake {
namespace graphics {
namespace gl {

enum class FramebufferBitFlag       { Color, Depth };
enum class PolygonMode              { Line, Fill };
enum class BufferTarget             { ArrayBuffer, ElementArrayBuffer };
enum class TextureTarget            { _2D, CubeMap };
enum class TextureParameter         { };
enum class Usage                    { StaticDraw };
enum class Capability               { CullFace };
enum class ShaderType               { Vertex, Fragment };
enum class PrimitiveType            { Lines, LineStrip, LineLoop, Triangles, TriangleStrip, TriangleFan };


enum class TextureFormat            { R, RGB, RGBA      };

enum class TextureWrap              { ClampToEdge };

enum class Filter                   { Nearest, Linear };

enum class SizedInternalFormat      { RGBA8 };

enum class Type                     { Float, UnsignedByte };

enum class PixelStorageMode         { PackAlignment, UnpackAlignment };

enum class NamedTextureUnit : uint8_t    
{ 
    Albedo = 0, 
    Skybox = 1 
};

inline TextureUnitIndex to_texture_unit_index( const NamedTextureUnit named_texture_unit )
{
    return TextureUnitIndex { underlying_cast( named_texture_unit ) };
}

enum class NamedVertexAttributeIndex : uint8_t
{
    Position2f  = 0,
    TextureCoordinates2f  = 1,

    Position3f  = 2,
    Normal3f  = 3,

    VoxelIdx3   = 4,
    VoxelTex2   = 5
};

inline AttributeIndex to_vertex_attribute_index( const NamedVertexAttributeIndex named_vertex_attribute_location )
{
    return AttributeIndex { underlying_cast( named_vertex_attribute_location ) }; 
}







} // namespace gl
} // namespace graphics
} // namespace shake

#endif // GL_ENUM_HPP
