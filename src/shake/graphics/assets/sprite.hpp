#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "shake/core/math/math.hpp"
#include "shake/core/macros/macro_property.hpp"
#include "shake/graphics/material/texture.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class Sprite
{
public:
    Sprite
    (
        const float         width,
        const float         height,
        const std::shared_ptr<Texture>& texture
    )
        : m_width       { width         }
        , m_height      { height        }
        , m_texture     { texture       }
        //, m_geometry    { width, height }
    { }

    PROPERTY_R( float,          width       )
    PROPERTY_R( float,          height      )
    PROPERTY_R( std::shared_ptr<Texture>,   texture     )
    //PROPERTY_R( Rectangle2D,    geometry    )
};

} // namespace graphics
} // namespace shake

#endif // SPRITE_HPP
