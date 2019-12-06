#ifndef VAO_HPP
#define VAO_HPP

#include <memory>
#include <cstdint>
#include <array>

#include "shake/core/macros/macro_non_copyable.hpp"

#include "shake/graphics/gl/gl_int.hpp"
#include "shake/graphics/vertex_attribute.hpp"
#include "shake/graphics/vertex_format.hpp"

namespace shake {
namespace graphics {

class Vao
{
public:
    using Ptr = std::shared_ptr<Vao>;

public:
    Vao();
    ~Vao();

    NON_COPYABLE( Vao )

    void bind() const;

    void specify_enable_vertex_format( const VertexFormat& vertex_format );

    void specify_enable_vertex_format_instanced( const VertexFormat& vertex_format );

    void specify_vertex_attrib
    (
        VertexAttribute::Location   location,
        VertexAttribute::Size       size,
        uint32_t                    stride,
        uint32_t                    offset
    );

    void enable_vertex_attrib       ( VertexAttribute::Location location );
    void disable_vertex_attrib      ( VertexAttribute::Location location );
    void set_vertex_attrib_divisor  ( VertexAttribute::Location location, const uint32_t divisor );

private:

    gl::VaoId m_id;
    std::array<VertexAttribute, 16> m_vertex_attributes;
};

void fill_vao
(
          Vao&                      vao,
    const std::vector<float>&       vertices,
    const VertexFormat&             vertex_format
);

void fill_vao
(
          Vao&                      vao,
    const std::vector<float>&       vertices,
    const std::vector<uint32_t>&    indices,
    const VertexFormat&             vertex_format
);

} // namespace graphics
} // namespace shake

#endif // VAO_HPP
