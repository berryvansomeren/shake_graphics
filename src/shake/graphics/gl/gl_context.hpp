#ifndef SHAKE_GRAPHICS_GL_GL_STATE_HPP
#define SHAKE_GRAPHICS_GL_GL_STATE_HPP

#include <array>

#include "shake/core/macros/macro_property.hpp"

#include "shake/graphics/gl/gl_enum.hpp"
#include "shake/graphics/gl/gl_int.hpp"

namespace shake {
namespace graphics {
namespace gl {

class Context
{
public:
    Context()
        : m_active_texture_unit_index { 0 }
    { }

private:
    struct TextureUnit
    {
        // You could technically bind multiple resources to different targets in the same texture unit
        // But because a shader won't allow you to use different targets of the same texture unit, 
        // you can effectively have only one functioning target current at a time.
        // Therefore, instead of having a field for every type of texture target,
        // we only keep track of the last bound texture target.
        TextureTarget   currently_bound_texture_target  = TextureTarget::_2D;
        TextureId       currently_bound_texture_id      = TextureId { 0 };
    };

    // Can't pass a type with commas to a macro
    // so we use an alias instead
    using TextureUnitArray = std::array< TextureUnit, 16 >;

    // The context has a limited number of texture units that can be bound at the same time. 
    // The index of the texture unit corresponds to a sampler location specified in a shader.    
    PROPERTY_RW( TextureUnitArray, texture_units )
    PROPERTY_RW( TextureUnitIndex, active_texture_unit_index )

    PROPERTY_RW( PolygonMode, current_polygon_mode )

    PROPERTY_RW( bool, is_depth_test_enabled    )
    PROPERTY_RW( bool, is_face_culling_enabled  )
    PROPERTY_RW( bool, is_depth_mask_enabled    )
};

auto context = Context { };

} // namespace gl
} // namespace graphics
} // namespace shake

#endif // SHAKE_GRAPHICS_GL_GL_STATE_HPP
