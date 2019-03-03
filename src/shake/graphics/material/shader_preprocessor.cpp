#include "shader_preprocessor.hpp"

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/types/underlying_cast.hpp"

#include "shake/graphics/vertex_attribute.hpp"

namespace shake {
namespace graphics {
namespace shader_preprocessor {

namespace  { // anonymous

std::string get_default_shader_defines()
{
    return "#version 430 core\n";

}

std::string get_default_vertex_shader_defines()
{
    return
        "#define SHAKE_VERTEX_SHADER\n"

        "#define SHAKE_VERTEX_POS2 " + std::to_string( underlying_cast( VertexAttribute::Location::VertexPos2 ) ) + "\n"
        "#define SHAKE_VERTEX_TEX2 " + std::to_string( underlying_cast( VertexAttribute::Location::VertexTex2 ) ) + "\n"

        "#define SHAKE_VERTEX_POS3 " + std::to_string( underlying_cast( VertexAttribute::Location::VertexPos3 ) ) + "\n"
        "#define SHAKE_VERTEX_NORM " + std::to_string( underlying_cast( VertexAttribute::Location::VertexNorm ) ) + "\n"

        "#define SHAKE_VOXEL_INDEX " + std::to_string( underlying_cast( VertexAttribute::Location::VoxelIdx3  ) ) + "\n"
        "#define SHAKE_VOXEL_TEX2 "  + std::to_string( underlying_cast( VertexAttribute::Location::VoxelTex2  ) ) + "\n"
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
    std::string Preprocess( const std::string& shader_source, const ShaderType shader_type ) const
    {
        auto result = std::string{ get_default_shader_defines() };
        switch (shader_type)
        {
        case ShaderType::Vertex:    result += get_default_vertex_shader_defines();      break;
        case ShaderType::Fragment:  result += get_default_fragment_shader_defines();    break;
        default: CHECK_FAIL( "Did not recognize shader type." ); break;
        }
        result += shader_source;
        return result;
    }
};

ShaderPreprocessor g_shader_preprocessor {};

} // namespace anonymous

std::string Preprocess( const std::string& shader_source, const ShaderType shader_type )
{
    return g_shader_preprocessor.Preprocess( shader_source, shader_type );
}

} // namespace shader_preprocessor
} // namespace graphics
} // namespace shake
