#include "draw.hpp"

#include "shake/graphics/context.hpp"


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

    material->unbind();
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

    material->unbind();
}

} // namespace graphics
} // namespace shake