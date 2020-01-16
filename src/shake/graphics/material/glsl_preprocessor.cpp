#include "glsl_preprocessor.hpp"

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/type_traits/underlying_cast.hpp"

namespace shake {
namespace graphics {
namespace glsl_preprocessor {

namespace  { // anonymous

std::string get_default_shader_defines()
{
    return "#version 430 core\n";

}

std::string get_default_vertex_shader_defines()
{
    return
        "#define SHAKE_VERTEX_SHADER\n"

        "#define SHAKE_VERTEX_POS2 " + std::to_string( underlying_cast( gl::NamedVertexAttributeIndex::Position2f ) ) + "\n"
        "#define SHAKE_VERTEX_TEX2 " + std::to_string( underlying_cast( gl::NamedVertexAttributeIndex::TextureCoordinates2f ) ) + "\n"

        "#define SHAKE_VERTEX_POS3 " + std::to_string( underlying_cast( gl::NamedVertexAttributeIndex::Position3f ) ) + "\n"
        "#define SHAKE_VERTEX_NORM " + std::to_string( underlying_cast( gl::NamedVertexAttributeIndex::Normal3f ) ) + "\n"

        "#define SHAKE_VOXEL_INDEX " + std::to_string( underlying_cast( gl::NamedVertexAttributeIndex::VoxelIdx3  ) ) + "\n"
        "#define SHAKE_VOXEL_TEX2 "  + std::to_string( underlying_cast( gl::NamedVertexAttributeIndex::VoxelTex2  ) ) + "\n"
    ;
}

std::string get_default_fragment_shader_defines()
{
    return "#define SHAKE_FRAGMENT_SHADER\n";
}

// Shader preprocessor RAII object
class ShaderPreprocessor
{
public:
    std::string preprocess( const std::string& shader_source, const gl::ShaderType shader_type ) const
    {
        auto result = std::string{ get_default_shader_defines() };
        switch (shader_type)
        {
        case gl::ShaderType::Vertex:    result += get_default_vertex_shader_defines();      break;
        case gl::ShaderType::Fragment:  result += get_default_fragment_shader_defines();    break;
        default: CHECK_FAIL( "Did not recognize shader type." ); break;
        }
        result += shader_source;
        return result;
    }
};

ShaderPreprocessor g_shader_preprocessor {};

} // namespace anonymous

std::string preprocess( const std::string& shader_source, const gl::ShaderType shader_type )
{
    return g_shader_preprocessor.preprocess( shader_source, shader_type );
}

} // namespace shader_preprocessor
} // namespace graphics
} // namespace shake
