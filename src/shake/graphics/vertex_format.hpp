#ifndef VERTEX_FORMAT_HPP
#define VERTEX_FORMAT_HPP

#include <vector>

#include "shake/core/type_traits/underlying_cast.hpp"

#include "shake/graphics/vertex_attribute.hpp"

namespace shake {
namespace graphics {

struct VertexFormatElement
{
    VertexAttribute::Location  location;
    VertexAttribute::Size      size;
};

using VertexFormat = std::vector<VertexFormatElement>;

inline
size_t compute_vertex_size( const VertexFormat& vertex_format )
{
    auto vertex_size = static_cast<size_t>( 0 );
    for ( const auto& vertex_format_element : vertex_format )
    {
        vertex_size += underlying_cast( vertex_format_element.size );
    }
    return vertex_size;
}

namespace VertexFormats
{
    const VertexFormat Pos2
    {
        { VertexAttribute::Location::VertexPos2,    VertexAttribute::Size::_2 }
    };

    const VertexFormat Pos2Tex2
    {
        { VertexAttribute::Location::VertexPos2,    VertexAttribute::Size::_2 },
        { VertexAttribute::Location::VertexTex2,    VertexAttribute::Size::_2 }
    };

    const VertexFormat Pos3
    {
        { VertexAttribute::Location::VertexPos3,    VertexAttribute::Size::_3 }
    };

    const VertexFormat Pos3Tex2
    {
        { VertexAttribute::Location::VertexPos3,    VertexAttribute::Size::_3 },
        { VertexAttribute::Location::VertexTex2,    VertexAttribute::Size::_2 }
    };

    const VertexFormat Pos3Nor3
    {
        { VertexAttribute::Location::VertexPos3,    VertexAttribute::Size::_3 },
        { VertexAttribute::Location::VertexNorm,    VertexAttribute::Size::_3 }
    };

    const VertexFormat Pos3Tex2Nor3
    {
        { VertexAttribute::Location::VertexPos3,    VertexAttribute::Size::_3 },
        { VertexAttribute::Location::VertexTex2,    VertexAttribute::Size::_2 },
        { VertexAttribute::Location::VertexNorm,    VertexAttribute::Size::_3 }
    };

    const VertexFormat VoxelIdx3Tex2
    {
        { VertexAttribute::Location::VoxelIdx3,     VertexAttribute::Size::_3 },
        { VertexAttribute::Location::VoxelTex2,     VertexAttribute::Size::_2 }
    };
}

} // namespace graphics
} // namespace shake

#endif // VERTEX_FORMAT_HPP
