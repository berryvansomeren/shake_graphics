#ifndef CUBE_MAP_HPP
#define CUBE_MAP_HPP

#include <array>
#include <memory>
#include <cstdint>

#include "shake/graphics/gl/gl.hpp"

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/macros/macro_non_copyable.hpp"
#include "shake/graphics/material/texture_parameters.hpp"

namespace shake {
namespace graphics {

class CubeMap
{
public:
    constexpr static size_t n_cube_faces = 6;

    // expected order is for each dimension (x, y, z),
    // first the positive, and then the negative;
    // right, left, top, bottom, front, back

    struct ImageInfo
    {
        uint8_t*    ptr;
        int         width;
        int         height;
    };

    using ImageData = std::array<ImageInfo, n_cube_faces>;

public:
    CubeMap::CubeMap
    (
        const ImageData&            image_data,
        const gl::TextureFormat     texture_format,
        const gl::Filter            filter
    );

    ~CubeMap();

    NON_COPYABLE( CubeMap )

    void bind( gl::TextureUnitIndex texture_unit ) const;

private:
    gl::TextureId m_id;
};

} // namespace graphics
} // namespace shake

#endif // CUBE_MAP_HPP
