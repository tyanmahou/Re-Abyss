#include <abyss/commons/Game/RenderStateInitializer.hpp>

namespace abyss
{
    void RenderStateInitializer::Init()
    {
        Graphics2D::Internal::SetSamplerState(ShaderStage::Vertex, 0, SamplerState::ClampNearest);
        Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 0, SamplerState::ClampNearest);
        Graphics2D::Internal::SetSamplerState(ShaderStage::Vertex, 1, SamplerState::BorderNearest);
        Graphics2D::Internal::SetSamplerState(ShaderStage::Pixel, 1, SamplerState::BorderNearest);
    }
}
