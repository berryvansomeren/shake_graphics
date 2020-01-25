#ifndef UNIFORM_MAP_HPP
#define UNIFORM_MAP_HPP

#include <memory>

#include "shake/core/ranges/index_range.hpp"
#include "shake/core/std/map.hpp"
#include "shake/graphics/gl/gl_int.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
using UniformMap = Map< std::string, gl::UniformLocation>;

//----------------------------------------------------------------
UniformMap get_uniform_map( const gl::ProgramId& program_id );

} // namespace graphics
} // namespace shake

#endif // UNIFORM_MAP_HPP
