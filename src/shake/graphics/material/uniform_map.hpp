#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <memory>

namespace shake {
namespace graphics {

using UniformMap = Map< std::string, gl::UniformLocation>;

UniformMap get_uniform_map( const ProgramId& program_id )
{
    
    const auto active_uniform_max_length = gl::get_program_iv_active_uniform_max_lenght( program_id );
    auto uniform_map = UniformMap { };



}

} // namespace graphics
} // namespace shake

#endif // UNIFORM_HPP
