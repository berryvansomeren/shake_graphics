

enum class TextureParameter
{
    DepthStencilTextureMode,
    BaseLevel,
    CompareFunc,
    CompareMode,
    LodBias,
    MinFilter,
    MagFilter,
    MinLod,
    MaxLod,
    MaxLevel,
    SwizzleR,
    SwizzleG,
    SwizzleB,
    SwizzleA,
    SwizzleS,
    SwizzleT,
    SwizzleR
};

constexpr GLenum texture_parameter_to_gl( const TextureParameter parameter )
{
    return Map<TextureParameter, GLenum>
    {
        { DepthStencilTextureMode, GL_DEPTH_STENCIL_TEXTURE_MODE }
    }.at( parameter );
}