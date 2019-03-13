#include "context.hpp"

#include <array>

#include <glad/glad.h>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/types/underlying_cast.hpp"
#include "shake/graphics/gl_debug_message.hpp"

namespace shake {
namespace graphics {
namespace gl {

namespace { // anonymous

uint32_t current_shader_id      = 0;
uint32_t current_vbo_id         = 0;
uint32_t current_ebo_id         = 0;
uint32_t current_vao_id         = 0;

std::array<uint32_t, 16> current_texture_unit_ids = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

PolygonMode current_polygon_mode = PolygonMode::Fill;

bool is_depth_test_enabled      = false;
bool is_face_culling_enabled    = false;
bool is_depth_mask_enabled      = false;

GLenum PrimitiveTypeToGlMode( const PrimitiveType primitive_type )
{
    switch ( primitive_type )
    {
    case PrimitiveType::Lines:          return GL_LINES;            break;
    case PrimitiveType::LineLoop:       return GL_LINE_LOOP;        break;
    case PrimitiveType::LineStrip:      return GL_LINE_STRIP;       break;
    case PrimitiveType::Triangles:      return GL_TRIANGLES;        break;
    case PrimitiveType::TriangleStrip:  return GL_TRIANGLE_STRIP;   break;
    case PrimitiveType::TriangleFan:    return GL_TRIANGLE_FAN;     break;
    default: CHECK_FAIL( "Unsupported PrimitiveType" ); break;
    }
}

uint32_t framebuffer_bit_flag_to_gl( const FramebufferBitFlag framebuffer_bit_flag )
{
    if ( framebuffer_bit_flag == FramebufferBitFlag::Color ) { return GL_COLOR_BUFFER_BIT; }
    if ( framebuffer_bit_flag == FramebufferBitFlag::Depth ) { return GL_DEPTH_BUFFER_BIT; }
    CHECK_FAIL( "Unsupported FramebufferBitFlag" );
}

uint32_t polygon_mode_to_gl( const PolygonMode polygon_mode )
{
    if ( polygon_mode == PolygonMode::Line ) { return GL_LINE; }
    if ( polygon_mode == PolygonMode::Fill ) { return GL_FILL; }
    CHECK_FAIL( "Unsupported PolygonMode" );
}

} // namespace anonymous

void init( const GLLoadProc& gl_load_proc )
{
    const auto load_success = gladLoadGLLoader( ( GLADloadproc ) gl_load_proc );
    if ( !load_success ) 
    {
        CHECK_FAIL( "Could not initialize OpenGl Context" );
    }
    glGetString(GL_VERSION); // todo remove

    glDebugMessageCallback( (GLDEBUGPROC) debug_message::callback, 0 );

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
}

void clear ( std::vector<FramebufferBitFlag> framebuffer_bit_flags )
{
    int flags_combined { 0 };
    for ( const auto& flag : framebuffer_bit_flags ) { flags_combined |= framebuffer_bit_flag_to_gl( flag ); }
    glClear( flags_combined );
}

uint32_t    get_current_shader_id()                     { return current_shader_id;         }
void        set_current_shader_id( uint32_t shader_id ) { current_shader_id = shader_id;    }

uint32_t    get_current_vbo_id()                        { return current_vbo_id;            }
void        set_current_vbo_id( uint32_t vbo_id )       { current_vbo_id = vbo_id;          }

uint32_t    get_current_ebo_id()                        { return current_ebo_id;            }
void        set_current_ebo_id( uint32_t ebo_id )       { current_ebo_id = ebo_id;          }

uint32_t    get_current_vao_id()                        { return current_vao_id;            }
void        set_current_vao_id( uint32_t vao_id )       { current_vao_id = vao_id;          }

uint32_t    get_current_texture_id( uint8_t texture_unit_index )                        { return current_texture_unit_ids[texture_unit_index];        }
void        set_current_texture_id( uint8_t texture_unit_index, uint32_t texture_id )   { current_texture_unit_ids[texture_unit_index] = texture_id;  }

PolygonMode get_current_polygon_mode() { return current_polygon_mode; }
void        set_current_polygon_mode( const PolygonMode polygon_mode )
{
    current_polygon_mode = polygon_mode;
    glPolygonMode( GL_FRONT_AND_BACK, polygon_mode_to_gl( polygon_mode ) );
}

void draw_primitive( const Primitive2D& primitive )
{
    primitive.get_has_index_buffer()
        ? draw_elements( primitive.get_type(), primitive.get_count() )
        : draw_arrays(   primitive.get_type(), primitive.get_count() );
}

void draw_primitive( const Primitive3D& primitive )
{
    primitive.get_has_index_buffer()
        ? draw_elements( primitive.get_type(), primitive.get_count() )
        : draw_arrays(   primitive.get_type(), primitive.get_count() );
}

void draw_arrays( const PrimitiveType primitive_type, const size_t count,  const size_t first )
{
    glDrawArrays( PrimitiveTypeToGlMode( primitive_type ), first, count );
}

void draw_elements( const PrimitiveType primitive_type, const size_t count )
{
    glDrawElements( PrimitiveTypeToGlMode( primitive_type ), count, GL_UNSIGNED_INT, nullptr );
}

void draw_elements_instanced( const PrimitiveType primitive_type, const size_t index_count, const size_t instance_count )
{
    glDrawElementsInstanced( PrimitiveTypeToGlMode( primitive_type ), index_count, GL_UNSIGNED_INT, nullptr, instance_count );
}

void enable_depth_mask()    
{
    if ( !is_depth_mask_enabled   ) 
    { 
        glDepthMask(GL_TRUE);       
        is_depth_mask_enabled = true;       
    } 
}

void disable_depth_mask()   
{ 
    if ( is_depth_mask_enabled ) 
    { 
        glDepthMask(GL_FALSE);      
        is_depth_mask_enabled = false;      
    } 
}

void enable_depth_test()    
{ 
    if ( !is_depth_test_enabled ) 
    { 
        glEnable(GL_DEPTH_TEST);    
        is_depth_test_enabled = true;       
    } 
}

void disable_depth_test()   
{ 
    if ( is_depth_test_enabled ) 
    { 
        glDisable(GL_DEPTH_TEST);   
        is_depth_test_enabled = false;      
    } 
}

void enable_face_culling()  
{ 
    if ( !is_face_culling_enabled ) 
    { 
        glEnable(GL_CULL_FACE);     
        is_face_culling_enabled = true;     
    } 
}

void disable_face_culling()
{ 
    if ( is_face_culling_enabled  ) 
    { 
        glDisable(GL_CULL_FACE);    
        is_face_culling_enabled = false;    
    } }

} // namespace gl
} // namespace graphics
} // namespace shake
