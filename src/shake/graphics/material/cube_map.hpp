#ifndef CUBE_MAP_HPP
#define CUBE_MAP_HPP

#include <memory>
#include <cstdint>

#include <glad/glad.h>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/types/macro_non_copyable.hpp"
#include "shake/graphics/material/texture_parameters.hpp"

namespace shake {
namespace graphics {

class CubeMap
{
public:
    using Ptr = std::shared_ptr<CubeMap>;

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
    CubeMap
    (
        const ImageData&        image_data,
        const ImageFormat       image_format,
        const TextureFormat     texture_format,
        const InterpolationMode interpolation_mode,
        const bool              generate_mip_maps
    );

    ~CubeMap();

    NON_COPYABLE( CubeMap )

    void bind   ( TextureUnit texture_unit_id ) const;
    void unbind () const;

private:
    std::uint32_t   m_id;
};

} // namespace graphics
} // namespace shake

#endif // CUBE_MAP_HPP
