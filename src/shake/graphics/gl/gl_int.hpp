#ifndef GL_INT_HPP
#define GL_INT_HPP

#include "shake/core/macros/macro_strongly_typed_alias.hpp"

namespace shake {
namespace graphics {
namespace gl {

STRONGLY_TYPED_ALIAS( SizeI,            std::uint64_t );

STRONGLY_TYPED_ALIAS( BufferId,         std::uint32_t );
STRONGLY_TYPED_ALIAS( VaoId,            std::uint32_t );

STRONGLY_TYPED_ALIAS( ProgramId,        std::uint64_t );
STRONGLY_TYPED_ALIAS( ShaderId,         std::uint64_t );

STRONGLY_TYPED_ALIAS( UniformLocation,  std::int32_t );
STRONGLY_TYPED_ALIAS( AttributeIndex,   std::int32_t );

STRONGLY_TYPED_ALIAS( TextureId,        std::uint32_t );
STRONGLY_TYPED_ALIAS( TextureUnitIndex, std::int32_t );

} // namespace gl
} // namespace graphics
} // namespace shake

#endif // GL_INT_HPP
