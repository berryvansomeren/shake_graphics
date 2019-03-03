#ifndef DRAW_RENDER_PACK_HPP
#define DRAW_RENDER_PACK_HPP

#include "shake/core/math/transform_2d.hpp"
#include "shake/core/math/transform_3d.hpp"

//#include "shake/content/content_manager.hpp"

#include "shake/graphics/render_pack.hpp"

#include "shake/graphics/context.hpp"


namespace shake     {
namespace graphics  {

//----------------------------------------------------------------
inline
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

    shader->set_uniform( "u_model",         transform.get_matrix()          );
    // still have to support 2D camera
    shader->set_uniform( "u_projection",    get_current_ortho_projection()  );

    shader->set_uniform( "u_color", glm::vec3( 1.f ) );

    geometry->draw();

    material->unbind();
}

//----------------------------------------------------------------
inline
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

    shader->set_uniform( "u_model",         transform.get_matrix()          );
    shader->set_uniform( "u_view",          camera->get_view_matrix()       );
    shader->set_uniform( "u_projection",    camera->get_projection_matrix() );

    // shader->set_uniform( "u_color", glm::vec3( 1.f ) );

    geometry->draw();

    material->unbind();
}

} // namespace graphics
} // namespace shake

#endif // DRAW_RENDER_PACK_HPP
