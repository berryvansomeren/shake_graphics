#ifndef SHADER_TYPE_HPP
#define SHADER_TYPE_HPP

namespace shake {
namespace graphics {

enum class ShaderType
{
    Vertex,
    Fragment,
    Geometry,
    Compute,
    TesselationControl,
    TesselationEvaluation
};

} // namespace graphics
} // namespace shake

#endif // SHADER_TYPE_HPP
