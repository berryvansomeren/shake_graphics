#include "uniform.hpp"

namespace shake {
namespace graphics {

//----------------------------------------------------------------
// These functions are only defined here,
// because the vtable would otherwise be emitted in every translation unit.
// It's kinda dumb...

//----------------------------------------------------------------
AUniform::~AUniform() { }

//----------------------------------------------------------------
#define DEFINE_UNIFORM_CLASS_CONSTRUCTOR( name, uniform_type ) \
    Uniform##name :: Uniform##name ( uniform_type value ) \
        : m_value { value } { }

DEFINE_UNIFORM_CLASS_CONSTRUCTOR( Int32,   int32_t     )
DEFINE_UNIFORM_CLASS_CONSTRUCTOR( Float,   float       )
DEFINE_UNIFORM_CLASS_CONSTRUCTOR( Vec2,    glm::vec2   )
DEFINE_UNIFORM_CLASS_CONSTRUCTOR( Vec3,    glm::vec3   )
DEFINE_UNIFORM_CLASS_CONSTRUCTOR( Mat4,    glm::mat4   )

#undef DEFINE_UNIFORM_STRUCT

} // namespace graphics
} // namespace shake
