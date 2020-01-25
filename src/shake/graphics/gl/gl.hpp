#ifndef GL_HPP
#define GL_HPP

#include <vector>

#include <glm/glm.hpp>

#include "shake/graphics/gl/gl_enum.hpp"
#include "shake/graphics/gl/gl_int.hpp"

namespace shake {
namespace graphics {
namespace gl {

using LoaderFunctionAddress = void* (*) ( const char* name );

//----------------------------------------------------------------
void init( const LoaderFunctionAddress& gl_load_proc );

//----------------------------------------------------------------
// Context

void enable_depth_mask();
void disable_depth_mask();

void enable_depth_test();
void disable_depth_test();

void enable_face_culling();
void disable_face_culling();

void set_current_polygon_mode( const PolygonMode polygon_mode );

//----------------------------------------------------------------
// Drawing

void clear ( std::vector<FramebufferBitFlag> framebuffer_bit_flags );

void draw_arrays( const PrimitiveType primitive_type, const size_t count, const size_t first = 0 );

void draw_elements( const PrimitiveType primitive_type, const size_t count );

void draw_elements_instanced( const PrimitiveType primitive_type, const size_t index_count, const size_t instance_count );

//----------------------------------------------------------------
// Program

ProgramId create_program();
void delete_program( const ProgramId id );
void link_program( const ProgramId id );
void use_program( const ProgramId id );

bool get_program_iv_link_status( const ProgramId id );
bool get_program_iv_validate_status( const ProgramId id );
Int get_program_iv_active_uniforms( const ProgramId id );
Int get_program_iv_active_uniform_max_lenght( const ProgramId id );

void get_active_uniform( const ProgramId id, const Int uniform_index );

std::string get_program_info_log( const ProgramId program_id );
void validate_program( const ProgramId id );



//----------------------------------------------------------------
// Shader

ShaderId create_shader( const ShaderType type );
void compile_shader( const ShaderId id );
void shader_source( const ShaderId id, const std::string& source );
void delete_shader( const ShaderId id );
void attach_shader( const ProgramId program_id, const ShaderId shader_id );

bool get_shader_iv_compile_status( const ShaderId id );
std::string get_shader_info_log( const ShaderId shader_id );

//----------------------------------------------------------------
// Uniform

std::pair<std::string,UniformLocation> get_active_uniform( const ProgramId id, const Int uniform_index, const Int max_uniform_name_length );
UniformLocation get_uniform_location( const ProgramId id, const std::string& name );

void program_uniform( const ProgramId program_id, const UniformLocation location, const glm::mat4& value    );
void program_uniform( const ProgramId program_id, const UniformLocation location, const glm::vec3& value    );
void program_uniform( const ProgramId program_id, const UniformLocation location, const glm::vec2& value    );
void program_uniform( const ProgramId program_id, const UniformLocation location, const float& value        );
void program_uniform( const ProgramId program_id, const UniformLocation location, const int32_t& value      );
void program_uniform( const ProgramId program_id, const UniformLocation location, const TextureUnitIndex value   );

//----------------------------------------------------------------
// Buffer

BufferId create_buffer();
void delete_buffer      ( const BufferId id );
void bind_buffer        ( const BufferTarget target, const BufferId id );
void named_buffer_data  ( const BufferId id, const Size size, const void* data, const Usage usage );

//----------------------------------------------------------------
// Vertex Array Object

VaoId create_vertex_array();
void delete_vertex_array( const VaoId id );
void bind_vertex_array  ( const VaoId id );

void enable_vertex_array_attrib( const VaoId id, const AttributeIndex index );
void disable_vertex_array_attrib( const VaoId id, const AttributeIndex index );

void vertex_array_vertex_buffer
(
    VaoId id, 
    BindingIndex binding_index,
    VboId vbo_id,
    Offset offset,
    Size stride
);

void vertex_array_attrib_format
( 
    const VaoId             id, 
    const AttributeIndex    index,
    const Size              size,
    const Type              type,
    const bool              normalized,
    const Offset            relative_offset
);

void vertex_array_attrib_binding
(
    const VaoId id,
    const AttributeIndex attribute_index,
    const BindingIndex binding_index
);

//----------------------------------------------------------------
// Texture

TextureId gen_texture();
void delete_texture     ( const TextureId id );
void bind_texture       ( const TextureTarget target, const TextureId id );
void active_texture     ( const TextureUnitIndex unit );

void texture_parameter  ( const TextureId id, const TextureWrap wrap );
void texture_parameter  ( const TextureId id, const Filter filter );

void texture_storage_2d
(
    const TextureId             id, 
    const uint8_t               n_levels,
    const SizedInternalFormat   internal_format,
    const Size                 width,
    const Size                 height
);

void texture_sub_image_2d
(
    const TextureId     id,
    const uint8_t       level,
    const std::uint64_t x_offset,
    const std::uint64_t y_offset,
    const Size         width,
    const Size         height,
    const TextureFormat format,
    const Type          type,
    const void*         data
);

void pixel_store( const PixelStorageMode mode, const Size size );

} // namespace gl
} // namespace graphics
} // namespace shake

#endif // GL_HPP
