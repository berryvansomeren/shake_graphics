#include "gl.hpp"

#include <array>

#include <glad/glad.h>

#include "shake/core/std/map.hpp"
#include "shake/core/contracts/check.hpp"
#include "shake/core/contracts/contracts.hpp"
#include "shake/core/macros/macro_define_mapping.hpp"
#include "shake/core/math/math.hpp"
#include "shake/core/type_traits/underlying_cast.hpp"
#include "shake/graphics/gl/gl_debug_message.hpp"

#include "shake/graphics/gl/gl_context.hpp"

namespace shake {
namespace graphics {
namespace gl {

namespace { // anonymous
    
DEFINE_MAPPING( GLint, to_glint, PrimitiveType,
    { PrimitiveType::Lines,         GL_LINES            },
    { PrimitiveType::LineLoop,      GL_LINE_LOOP        },
    { PrimitiveType::LineStrip,     GL_LINE_STRIP       },
    { PrimitiveType::Triangles,     GL_TRIANGLES        },
    { PrimitiveType::TriangleStrip, GL_TRIANGLE_STRIP   },
    { PrimitiveType::TriangleFan,   GL_TRIANGLE_FAN     }
)

DEFINE_MAPPING( GLint, to_glint, FramebufferBitFlag, 
    { FramebufferBitFlag::Color,    GL_COLOR_BUFFER_BIT },
    { FramebufferBitFlag::Depth,    GL_DEPTH_BUFFER_BIT }
)

DEFINE_MAPPING( GLint, to_glenum, PolygonMode, 
    { PolygonMode::Line,            GL_LINE             },
    { PolygonMode::Fill,            GL_FILL             }
)

DEFINE_MAPPING( GLenum, to_glenum, BufferTarget,
    { BufferTarget::ArrayBuffer,        GL_ARRAY_BUFFER             },
    { BufferTarget::ElementArrayBuffer, GL_ELEMENT_ARRAY_BUFFER     }
)

DEFINE_MAPPING( GLenum, to_glenum, Usage,
    { Usage::StaticDraw, GL_STATIC_DRAW }
)

DEFINE_MAPPING( GLenum, to_glenum, TextureTarget,
    { TextureTarget::_2D, GL_TEXTURE_2D }
)

DEFINE_MAPPING( GLenum, to_glenum, ShaderType,
    { ShaderType::Vertex,   GL_VERTEX_SHADER    },
    { ShaderType::Fragment, GL_FRAGMENT_SHADER  }
)

DEFINE_MAPPING( bool, to_bool, GLint,
    { GL_TRUE,  true    },
    { GL_FALSE, false   }
)

DEFINE_MAPPING( GLenum, to_glenum, SizedInternalFormat,
    { SizedInternalFormat::RGBA8,    GL_RGBA8   }
)

DEFINE_MAPPING( GLenum, to_glenum, TextureFormat,
    { TextureFormat::R,       GL_RED      },
    { TextureFormat::RGB,     GL_RGB      },
    { TextureFormat::RGBA,    GL_RGBA     }
)

DEFINE_MAPPING( GLenum, to_glint, TextureWrap,
    { TextureWrap::ClampToEdge,  GL_CLAMP_TO_EDGE   }
)

DEFINE_MAPPING( GLenum, to_glint, Filter,
    { Filter::Linear,    GL_LINEAR   },
    { Filter::Nearest,   GL_NEAREST  }
)

DEFINE_MAPPING( GLenum, to_glenum, Type,
    { Type::Float,           GL_FLOAT           },       
    { Type::UnsignedByte,    GL_UNSIGNED_BYTE   }
)

DEFINE_MAPPING( GLenum, to_glenum, PixelStorageMode,
    { PixelStorageMode::PackAlignment,      GL_PACK_ALIGNMENT       },
    { PixelStorageMode::UnpackAlignment,    GL_UNPACK_ALIGNMENT     }
)

inline GLsizei to_glsizei( const Size size )
{
    return static_cast<GLsizei>( *size );
}

inline GLint to_glint( const Size size )
{
     return static_cast<GLint>( *size );
}

inline GLint to_glint( const std::uint64_t v )
{
    return static_cast<GLint>( v );
}

inline GLint to_gluint( const std::uint32_t v )
{
    return static_cast<GLuint>( v );
}

inline GLint to_glint( const TextureUnitIndex v )
{
    return static_cast<GLint>( *v );
}

inline GLuint to_gluint( const VaoId id )
{
    return to_gluint( *id );
}

inline GLuint to_gluint( const AttributeIndex index )
{
    return to_gluint( *index );
}


} // namespace anonymous


//----------------------------------------------------------------
void init( const LoaderFunctionAddress& gl_load_proc )
{
    const auto load_success = gladLoadGLLoader( ( LoaderFunctionAddress ) gl_load_proc );
    if ( !load_success ) 
    {
        CHECK_FAIL( "Could not initialize OpenGl Context" );
    }

    const auto gl_string_to_std_string = []( const GLubyte* s ) { return std::string { reinterpret_cast< char const * >( s ) }; };

    LOG( std::string { "GL version: "   } + gl_string_to_std_string( glGetString( GL_VERSION ) ) ); // todo remove
    LOG( std::string { "GL vendor: "    } + gl_string_to_std_string( glGetString( GL_VENDOR ) ) );
    LOG( std::string { "GL renderer: "  } + gl_string_to_std_string( glGetString( GL_RENDERER ) ) );
    LOG( std::string { "GLSL version: " } + gl_string_to_std_string( glGetString( GL_SHADING_LANGUAGE_VERSION) ) );

    // enable debug output
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( (GLDEBUGPROC) gl::debug_message::callback, 0 );

    // Enable depth (Z) buffer (accept "closest" fragment)
    enable_depth_test();
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    enable_face_culling();

    // Enable blending with alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default colour after clearing the colour buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // TODO: Required for freetype? or can be removed?
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
}

void clear ( std::vector<FramebufferBitFlag> framebuffer_bit_flags )
{
    int flags_combined { 0 };
    for ( const auto& flag : framebuffer_bit_flags ) { flags_combined |= to_glint( flag ); }
    glClear( flags_combined );
}


//void draw_primitive( const Primitive2D& primitive )
//{
//    primitive.get_has_index_buffer()
//        ? draw_elements( primitive.get_type(), primitive.get_count() )
//        : draw_arrays(   primitive.get_type(), primitive.get_count() );
//}
//
//void draw_primitive( const Primitive3D& primitive )
//{
//    primitive.get_has_index_buffer()
//        ? draw_elements( primitive.get_type(), primitive.get_count() )
//        : draw_arrays(   primitive.get_type(), primitive.get_count() );
//}

void draw_arrays( const PrimitiveType primitive_type, const size_t count,  const size_t first )
{
    glDrawArrays( to_glint( primitive_type ), first, count );
}

void draw_elements( const PrimitiveType primitive_type, const size_t count )
{
    glDrawElements( to_glint( primitive_type ), count, GL_UNSIGNED_INT, nullptr );
}

void draw_elements_instanced( const PrimitiveType primitive_type, const size_t index_count, const size_t instance_count )
{
    glDrawElementsInstanced( to_glint( primitive_type ), index_count, GL_UNSIGNED_INT, nullptr, instance_count );
}

void enable_depth_mask()    
{
    if ( !context.is_depth_mask_enabled() )
    {
        glDepthMask(GL_TRUE);    
        context.is_depth_mask_enabled() = true;
    }
}

void disable_depth_mask()   
{ 
    if ( context.is_depth_mask_enabled() )
    {
        glDepthMask(GL_FALSE); 
        context.is_depth_mask_enabled() = false;
    }
}

void enable_depth_test()    
{ 
    if ( !context.is_depth_test_enabled() )
    {
        glEnable(GL_DEPTH_TEST);  
        context.is_depth_test_enabled() = true;
    }
}

void disable_depth_test()   
{ 
    if ( context.is_depth_test_enabled() )
    {
        glDisable(GL_DEPTH_TEST);  
        context.is_depth_test_enabled() = false;
    }
}

void enable_face_culling()  
{ 
    if ( !context.is_face_culling_enabled() )
    {
        glEnable(GL_CULL_FACE); 
        context.is_face_culling_enabled() = true;
    }
}

void disable_face_culling()
{ 
    if ( context.is_face_culling_enabled() )
    {
        glDisable(GL_CULL_FACE);  
        context.is_face_culling_enabled() = false;
    }
}

void set_current_polygon_mode( const PolygonMode polygon_mode )
{
    if ( context.current_polygon_mode() != polygon_mode )
    {
        glPolygonMode( GL_FRONT_AND_BACK, to_glenum( polygon_mode ) );
        context.current_polygon_mode() = polygon_mode;
    }
}


ProgramId create_program()
{
    return ProgramId { glCreateProgram() };
}

void delete_program( const ProgramId id )
{
    glDeleteProgram( *id );
}

void link_program( const ProgramId id )
{
    glLinkProgram( *id );
}

void use_program( const ProgramId id )
{
    glUseProgram( *id );
}

bool get_program_iv_link_status( const ProgramId id )
{
    auto link_status = GLint { };
    glGetProgramiv( *id, GL_LINK_STATUS, &link_status );
    return to_bool( link_status );
}

void validate_program( const ProgramId id )
{
    glValidateProgram( *id );
}

bool get_program_iv_validate_status( const ProgramId id )
{
    auto validate_status = GLint { };
    glGetProgramiv( *id, GL_VALIDATE_STATUS, &validate_status );
    return to_bool( validate_status );
}

namespace { // anonymous


std::size_t get_program_iv_info_log_length( const ProgramId id )
{
    auto log_length = GLint { };
    glGetProgramiv( *id, GL_INFO_LOG_LENGTH, &log_length );
    return static_cast< std::size_t >( log_length );
}

bool get_program_iv_validate_status( const ProgramId id )
{
    auto validate_status = GLint { };
    glGetProgramiv( *id, GL_VALIDATE_STATUS, &validate_status );
    return to_bool( validate_status );
}

std::string get_program_info_log( const ProgramId id, std::size_t log_length )
{
    auto buffer = std::vector<GLchar>( log_length );
    glGetProgramInfoLog( *id, log_length, nullptr, buffer.data() );
    const auto message = std::string { std::begin( buffer ), std::end( buffer ) };
    return message;
}

} // namespace anonymous

std::string get_program_info_log( const ProgramId program_id )
{
    const auto log_length = gl::get_program_iv_info_log_length( program_id );
    return get_program_info_log( program_id, log_length );
}

Int get_program_iv_active_uniforms( const ProgramId id )
{
    auto n_active_uniforms = GLint { };
    glGetProgramiv( *id, GL_ACTIVE_UNIFORMS, &n_active_uniforms );
    return Int { static_cast< Int::value_type >( n_active_uniforms ) };
}

Int get_program_iv_active_uniform_max_lenght( const ProgramId id )
{
    auto active_uniform_max_length = GLint { };
    glGetProgramiv( *id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &active_uniform_max_length );
    return Int { static_cast< Int::value_type >( active_uniform_max_length ) };
}


ShaderId create_shader( const ShaderType type )
{
    return ShaderId { glCreateShader( to_glenum( type ) ) };
}

void compile_shader( const ShaderId id )
{
    glCompileShader( *id );
}

void shader_source( const ShaderId id, const std::string& source )
{
    const char* source_ptr { source.c_str() };
    glShaderSource( *id, 1, &source_ptr, nullptr );
}

void delete_shader( const ShaderId id )
{
    glDeleteShader( *id );
}

void attach_shader( const ProgramId program_id, const ShaderId shader_id )
{
    glAttachShader( *program_id, *shader_id );
}

bool get_shader_iv_compile_status( const ShaderId id )
{
    auto compile_status = GLint { };
    glGetShaderiv( *id, GL_COMPILE_STATUS, &compile_status );
    return to_bool( compile_status );
}

namespace { // anonymous

    std::size_t get_shader_iv_info_log_length( const ShaderId id )
    {
        auto log_length = GLint { };
        glGetShaderiv( *id, GL_INFO_LOG_LENGTH, &log_length );
        return static_cast<std::size_t>( log_length );
    }

    std::string get_shader_info_log( const ShaderId id, std::size_t log_length )
    {
        auto buffer = std::vector<GLchar>( log_length );
        glGetShaderInfoLog( *id, log_length, nullptr, buffer.data() );
        const auto message = std::string { std::begin( buffer ), std::end( buffer ) };
        return message;
    }

} // namespace anonymous

std::string get_shader_info_log( const ShaderId shader_id )
{
    const auto log_length = gl::get_shader_iv_info_log_length( shader_id );
    return get_shader_info_log( shader_id, log_length );
}

std::pair<std::string,UniformLocation> get_active_uniform( const ProgramId id, const Int uniform_index, const Int max_uniform_name_length )
{
    auto name_length = GLsizei { };
    auto uniform_size = GLsizei { };
    auto uniform_type = GLenum { };
    auto uniform_name_buffer = std::vector< char > ( *max_uniform_name_length );
    glGetActiveUniform( *id, *uniform_index, *max_uniform_name_length, &name_length, &uniform_size, &uniform_type, uniform_name_buffer.data() );
    const auto uniform_name = std::string { std::begin( uniform_name_buffer ), std::begin( uniform_name_buffer ) + name_length };
    const auto uniform_location = get_uniform_location( id, uniform_name );
    return { uniform_name, uniform_location };
}


UniformLocation get_uniform_location( const ProgramId id, const std::string& name )
{
    const auto uniform_location = glGetUniformLocation( *id, name.c_str() );
    CHECK_GE( uniform_location, 0, "Could not find uniform " + name );
    return UniformLocation { uniform_location };
}

void program_uniform( const ProgramId program_id, UniformLocation location, const glm::mat4& value )
{
    glProgramUniformMatrix4fv( *program_id, *location, 1, GL_FALSE, glm::value_ptr( value ) );
}

void program_uniform( const ProgramId program_id, const UniformLocation location, const glm::vec3& value )
{
    glProgramUniform3f( *program_id, *location, value.x, value.y, value.z );
}

void program_uniform( const ProgramId program_id, const UniformLocation location, const glm::vec2& value )
{
    glProgramUniform2f( *program_id, *location, value.x, value.y );
}

void program_uniform( const ProgramId program_id, const UniformLocation location, const float& value )
{
    glProgramUniform1f( *program_id, *location, value );
}

void program_uniform( const ProgramId program_id, const UniformLocation location, const int32_t& value )
{
    glProgramUniform1i( *program_id, *location, value );
}

void program_uniform( const ProgramId program_id, const UniformLocation location, const TextureUnitIndex value )
{
    glProgramUniform1i( *program_id, *location, to_glint( value ) );
}

BufferId create_buffer()
{
    auto id = GLuint { };
    glCreateBuffers( 1, &id );
    return BufferId { id };
}

void delete_buffer( const BufferId id )
{
    glDeleteBuffers( 1, &id );
}

void bind_buffer( const BufferTarget target, const BufferId id )
{
    glBindBuffer( to_glenum( target ), *id );
}

void named_buffer_data( const BufferId id, const Size size, const void* data, const Usage usage )
{
    glNamedBufferData( *id, *size, data, to_glenum( usage ) );
}

//----------------------------------------------------------------
// Vertex Array Object

VaoId create_vertex_array()
{
    auto id = GLuint { };
    glCreateVertexArrays( 1, &id );
    return VaoId { id };
}

void bind_vertex_array( const VaoId id )
{
    glBindVertexArray( *id );
}

void delete_vertex_array( const VaoId id )
{
    glDeleteVertexArrays( 1, &id );
}

void enable_vertex_array_attrib( const VaoId id, const AttributeIndex index )
{
    glEnableVertexArrayAttrib( to_gluint( id ), to_gluint( index ) );
}

void disable_vertex_array_attrib( const VaoId id, const AttributeIndex index )
{
    glDisableVertexArrayAttrib( to_gluint( id ), to_gluint( index ) );
}

void vertex_array_attrib_format
(
    const VaoId             id,
    const AttributeIndex    index,
    const Size              size,
    const Type              type,
    const bool              normalized,
    const Offset            relative_offset
)
{
    glVertexArrayAttribFormat
    (
        *id,
        *index,
        *size,
        to_glenum( type ),
        normalized,
        *relative_offset
    );
}

void vertex_array_attrib_binding
(
    const VaoId id,
    const AttributeIndex attribute_index,
    const BindingIndex binding_index
)
{
    glVertexArrayAttribBinding( *id, *attribute_index, *binding_index );
}

void vertex_array_vertex_buffer
(
    const VaoId id,
    const BindingIndex binding_index,
    const VboId vbo_id,
    const Offset offset,
    const Size stride
)
{
    glVertexArrayVertexBuffer( *id, *binding_index, *vbo_id, *offset, *stride );
}

//----------------------------------------------------------------
// Texture


TextureId gen_texture()
{
    auto id = GLuint { };
    glGenTextures( 1, &id );
    return TextureId { id };

}

void delete_texture( const TextureId id )
{
    glDeleteTextures( 1, &id );
}

void bind_texture( const TextureTarget target, const TextureId id )
{
    glBindTexture( to_glenum( target ), *id );
    auto& active_texture_unit = context.texture_units().at( *context.active_texture_unit_index() );
    active_texture_unit.currently_bound_texture_target = target;
    active_texture_unit.currently_bound_texture_id = id;
}

void active_texture( const TextureUnitIndex texture_unit_index )
{
    if ( context.active_texture_unit_index() != texture_unit_index )
    {
        glActiveTexture( *texture_unit_index );
        context.active_texture_unit_index() = texture_unit_index;
    }
}

void texture_parameter( const TextureId id, const TextureWrap wrap )
{
    const auto glint_wrap = to_glint( wrap );
    glTextureParameteri( *id, GL_TEXTURE_WRAP_S, glint_wrap );
    glTextureParameteri( *id, GL_TEXTURE_WRAP_T, glint_wrap );
    glTextureParameteri( *id, GL_TEXTURE_WRAP_R, glint_wrap );
}

void texture_parameter( const TextureId id, const Filter filter )
{
    const auto glint_filter = to_glint( filter );
    glTextureParameteri( *id, GL_TEXTURE_MIN_FILTER, glint_filter );
    glTextureParameteri( *id, GL_TEXTURE_MAG_FILTER, glint_filter );
}

void texture_storage_2d
(
    const TextureId id,
    const uint8_t n_levels,
    const SizedInternalFormat internal_format,
    const Size width,
    const Size height
)
{
    glTextureStorage2D
    (
        *id,
        n_levels,
        to_glenum( internal_format ),
        static_cast<GLsizei>( *width ),
        static_cast<GLsizei>( *height )
    );
}


void texture_sub_image_2d
(
    const TextureId id,
    const uint8_t level,
    const std::uint64_t x_offset,
    const std::uint64_t y_offset,
    const Size width,
    const Size height,
    const TextureFormat format,
    const Type          type,
    const void*         data
)
{
    glTextureSubImage2D
    (
        *id,
        level,
        to_glint( x_offset ),
        to_glint( y_offset ),
        to_glsizei( width ),
        to_glsizei( height ),
        to_glenum( format ),
        to_glenum( type ),
        data
    );
}



void pixel_store( const PixelStorageMode mode, const Size size )
{
    glPixelStorei( to_glenum( mode ), to_glint( size ) );
}

} // namespace gl
} // namespace graphics
} // namespace shake
