#ifndef FONT_HPP
#define FONT_HPP

#include "shake/core/std/map.hpp"
#include "shake/core/math/math.hpp"

#include "shake/graphics/assets/sprite.hpp"

#include "shake/graphics/render_pack.hpp"

namespace shake {
namespace graphics {

class Font
{
public:
    struct Character
    {
        RenderPack2D    render_pack;
        glm::vec2       size;
        glm::ivec2      bearing;
        glm::ivec2      advance;
    };

    using CharacterMap = std::unordered_map<char, Character>;

    enum class Mode { Default, Bold, Itallic, BoldItallic };

public:
    Font
    (
        const CharacterMap& default_character_map,
        const CharacterMap& bold_character_map,
        const CharacterMap& itallic_character_map,
        const CharacterMap& bold_itallic_character_map
    )
        : m_default_characters      { default_character_map         }
        , m_bold_characters         { bold_character_map            }
        , m_itallic_characters      { itallic_character_map         }
        , m_bold_itallic_characters { bold_itallic_character_map    }
    { }

    const Character& get_character( const char c, const Mode mode = Mode::Default )
    {
        switch ( mode )
        {
        case Mode::Default:     return m_default_characters.at( c );        break;
        case Mode::Bold:        return m_bold_characters.at( c );           break;
        case Mode::Itallic:     return m_itallic_characters.at( c );        break;
        case Mode::BoldItallic: return m_bold_itallic_characters.at( c );   break;
        default: CHECK_FAIL( "Font::Mode was not recognised." ); break;
        }
        return m_default_characters.at( c );
    }

private:
    CharacterMap m_default_characters;
    CharacterMap m_bold_characters;
    CharacterMap m_itallic_characters;
    CharacterMap m_bold_itallic_characters;
};

} // namespace gl
} // namespace shake

#endif // FONT_HPP
