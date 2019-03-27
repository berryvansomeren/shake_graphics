#include "draw_text.hpp"

#include "shake/core/math/transform_2d.hpp"

#include "shake/graphics/draw.hpp"

namespace shake     {
namespace graphics  {

//----------------------------------------------------------------
void draw
(
    const std::string&              text,
    const glm::vec2&                position,
    const std::shared_ptr<Font>&    font
)
{
    glm::vec2 character_origin { position };

    for ( const char& c : text )
    {
        const auto& character   { font->get_character( c ) };
        auto character_position { character_origin };
        character_position.x += character.bearing.x;
        character_position.y -= character.size.y - character.bearing.y;
        const auto& transform = Transform2D().translate( character_position );

        draw( character.render_pack, transform );

        character_origin += character.advance;
    }
}

} // namespace graphics
} // namespace shake
