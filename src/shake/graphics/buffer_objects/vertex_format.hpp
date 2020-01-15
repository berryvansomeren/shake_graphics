#ifndef VERTEX_FORMAT_HPP
#define VERTEX_FORMAT_HPP

#include <vector>

#include "shake/core/type_traits/underlying_cast.hpp"

#include "shake/graphics/gl/gl_int.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
struct VertexAttributeFormat
{
    gl::AttributeIndex  attribute_index;
    gl::Size            attribute_element_count;
    gl::Type            attribute_type;
};

//----------------------------------------------------------------
using VertexFormat = std::vector<VertexAttributeFormat>;

//----------------------------------------------------------------
inline gl::Size get_vertex_size_in_bytes( const VertexFormat& vertex_format )
{
    auto vertex_size = gl::Size { 0 };
    for ( const auto& vertex_attribute : vertex_format )
    {
        const auto attribute_size = gl::Size
        {
            *vertex_attribute.attribute_element_count * sizeof( vertex_attribute.attribute_type )
        };

        *vertex_size += *attribute_size;
    }
    return vertex_size;
}

//----------------------------------------------------------------
namespace AttributeFormats
{
    const VertexAttributeFormat Position2f
    { 
        to_vertex_attribute_index( gl::NamedVertexAttributeIndex::Position2f ), 
        gl::Size { 2 },
        gl::Type::Float
    };

    const VertexAttributeFormat TextureCoordinates2f
    { 
        to_vertex_attribute_index( gl::NamedVertexAttributeIndex::TextureCoordinates2f ), 
        gl::Size { 2 },
        gl::Type::Float    
    };

    const VertexAttributeFormat Position3f
    { 
        to_vertex_attribute_index( gl::NamedVertexAttributeIndex::Position3f ), 
        gl::Size { 3 },
        gl::Type::Float
    };

    const VertexAttributeFormat Normal3f
    { 
        to_vertex_attribute_index( gl::NamedVertexAttributeIndex::Normal3f ),    
        gl::Size { 3 },
        gl::Type::Float
    };
}

//----------------------------------------------------------------
namespace VertexFormats
{
    const VertexFormat Pos2
    {
        AttributeFormats::Position2f
    };

    const VertexFormat Pos2Tex2
    {
        AttributeFormats::Position2f,
        AttributeFormats::TextureCoordinates2f
    };

    const VertexFormat Pos3
    {
        AttributeFormats::Position3f
    };

    const VertexFormat Pos3Tex2
    {
        AttributeFormats::Position3f,
        AttributeFormats::TextureCoordinates2f
    };

    const VertexFormat Pos3Nor3
    {
        AttributeFormats::Position3f,
        AttributeFormats::Normal3f
    };

    const VertexFormat Pos3Tex2Nor3
    {
        AttributeFormats::Position3f,
        AttributeFormats::TextureCoordinates2f,
        AttributeFormats::Normal3f
    };

    //const VertexFormat VoxelIdx3Tex2
    //{
    //    //{ VertexAttribute::Location::VoxelIdx3,     VertexAttribute::Size::_3 },
    //    //{ VertexAttribute::Location::VoxelTex2,     VertexAttribute::Size::_2 }
    //};
}

} // namespace graphics
} // namespace shake

#endif // VERTEX_FORMAT_HPP
