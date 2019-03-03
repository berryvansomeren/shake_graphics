#ifndef DRAW_TEXT_HPP
#define DRAW_TEXT_HPP

#include <string>

#include "shake/core/math/math.hpp"

namespace shake     {
namespace graphics  {

void draw
(
    const std::string&      text,
    const glm::vec2&        position,
    const std::string&      font_path   = "fonts/open_sans/open_sans.json"
);

} // namespace graphics
} // namespace shake

#endif // DRAW_TEXT_HPP
