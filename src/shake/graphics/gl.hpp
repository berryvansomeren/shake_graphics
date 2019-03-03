#ifndef GL_CONTEXT_HPP
#define GL_CONTEXT_HPP

#include <cstdint>
#include <vector>

#include <glad/glad.h>

#include "shake/graphics/geometry/primitive_2d.hpp"
#include "shake/graphics/geometry/primitive_3d.hpp"
#include "shake/graphics/geometry/primitive_type.hpp"

namespace shake {

using GLLoadProc = void* (*) ( const char* name );

namespace graphics {
namespace gl {

enum class FramebufferBitFlag   { Color,    Depth };
enum class PolygonMode          { Line,     Fill };

void        init( const GLLoadProc& gl_load_proc );

void        clear ( std::vector<FramebufferBitFlag> framebuffer_bit_flags );

uint32_t    get_current_shader_id   ();
void        set_current_shader_id   ( uint32_t shader_id );

uint32_t    get_current_vbo_id      ();
void        set_current_vbo_id      ( uint32_t vbo_id );

uint32_t    get_current_ebo_id      ();
void        set_current_ebo_id      ( uint32_t ebo_id );

uint32_t    get_current_vao_id      ();
void        set_current_vao_id      ( uint32_t vao_id );

uint32_t    get_current_texture_id  ( uint8_t texture_unit_index );
void        set_current_texture_id  ( uint8_t texture_unit_index, uint32_t texture_id );


PolygonMode get_current_polygon_mode();
void        set_current_polygon_mode( const PolygonMode polygon_mode );

void draw_primitive( const Primitive2D& primitive );
void draw_primitive( const Primitive3D& primitive );

void draw_arrays( const PrimitiveType primitive_type, const size_t count, const size_t first = 0 );

void draw_elements( const PrimitiveType primitive_type, const size_t count );

void draw_elements_instanced( const PrimitiveType primitive_type, const size_t index_count, const size_t instance_count );

void enable_depth_mask();
void disable_depth_mask();

void enable_depth_test();
void disable_depth_test();

void enable_face_culling();
void disable_face_culling();

} // namespace gl
} // namespace graphics
} // namespace shake

#endif // GL_CONTEXT_HPP
