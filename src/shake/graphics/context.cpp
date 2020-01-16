#include "context.hpp"

namespace shake     {
namespace graphics  {

namespace { // anonymous

glm::vec2                   g_current_screen_size       { };
std::shared_ptr<Camera>     g_current_camera            { };
glm::mat4                   g_current_ortho_projection  { };

} // namespace anonymous

//----------------------------------------------------------------
void set_current_screen_size( const glm::vec2& size )
{
    g_current_screen_size = size;
    set_current_ortho_projection( glm::ortho( 0.f, size.x, 0.f, size.y ) );
}

//----------------------------------------------------------------
glm::vec2 get_current_screen_size( )
{
    return g_current_screen_size;
}

//----------------------------------------------------------------
void set_current_camera( const std::shared_ptr<Camera>& camera )
{
    g_current_camera = camera;
}

//----------------------------------------------------------------
std::shared_ptr<Camera>& get_current_camera( )
{
    if ( g_current_camera )
    {
        return g_current_camera;
    }
    else
    {
        CHECK_FAIL("The current camera expired and can therefore not be bound.");
    }
}

//----------------------------------------------------------------
void set_current_ortho_projection( const glm::mat4& ortho_projection )
{
    g_current_ortho_projection = ortho_projection;
}

//----------------------------------------------------------------
glm::mat4 get_current_ortho_projection( )
{
    return g_current_ortho_projection;
}

} // namespace graphics
} // namespace shake
