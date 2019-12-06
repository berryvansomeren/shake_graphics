#include "draw.hpp"

#include "shake/graphics/context.hpp"

#include "shake/graphics/gl/gl_enum.hpp"


namespace shake     {
namespace graphics  {

//----------------------------------------------------------------
void draw
(
    const RenderPack2D& render_pack,
    const Transform2D&  transform
)
{
    const auto& material    = render_pack.material;
    const auto& geometry    = render_pack.geometry;
    const auto& shader      = material->get_shader();

    material->bind();

    shader->set_uniform( "u_SHAKE_MODEL",         transform.get_matrix()          );
    // still have to support 2D camera
    shader->set_uniform( "u_SHAKE_PROJECTION",    get_current_ortho_projection()  );

    shader->set_uniform( "u_color", glm::vec3( 1.f ) );

    geometry->draw();
}

//----------------------------------------------------------------
void draw
(
    const RenderPack3D& render_pack,
    const Transform3D&  transform
)
{
    const auto& material    = render_pack.material;
    const auto& geometry    = render_pack.geometry;
    const auto& shader      = material->get_shader();
    const auto& camera      = get_current_camera();

    material->bind();

    shader->try_set_uniform( "u_SHAKE_MODEL",       transform.get_matrix()          );
    shader->set_uniform( "u_SHAKE_VIEW",        camera->get_view_matrix()       );
    shader->set_uniform( "u_SHAKE_PROJECTION",  camera->get_projection_matrix() );

    // shader->set_uniform( "u_color", glm::vec3( 1.f ) );

    geometry->draw();
}


void draw( const Primitive2D& primitive )
{
    primitive.get_has_index_buffer()
        ? gl::draw_elements( primitive.get_type(), primitive.get_count() )
        : gl::draw_arrays(   primitive.get_type(), primitive.get_count() );
}

void draw( const Primitive3D& primitive )
{
    primitive.get_has_index_buffer()
        ? gl::draw_elements( primitive.get_type(), primitive.get_count() )
        : gl::draw_arrays(   primitive.get_type(), primitive.get_count() );
}

} // namespace graphics
} // namespace shake