#ifndef DRAW_TEXT_HPP
#define DRAW_TEXT_HPP

#include <string>

#include "shake/core/math/math.hpp"
#include "shake/graphics/assets/font.hpp"

namespace shake     {
namespace graphics  {

void draw
(
    const std::string&              text,
    const glm::vec2&                position,
    const std::shared_ptr<Font>&    font
);

} // namespace graphics
} // namespace shake

#endif // DRAW_TEXT_HPP
