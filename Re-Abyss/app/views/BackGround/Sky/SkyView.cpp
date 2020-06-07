#include "SkyView.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/views/Camera/CameraView.hpp>
namespace abyss
{
    SkyView::SkyView() :
        m_texture(ResourceManager::Main()->loadTexture(U"bgs/sky.png"))
    {

    }

    void SkyView::draw(const CameraView& camera) const
    {
        ScopedRenderStates2D blend(BlendState::Additive, SamplerState::MirrorNearest);
        auto shader = m_skyShader.start();
        auto tl = camera.screenRegion().tl();
        auto offset = Vec2{ 0, -tl.y / 20.0 };
        m_texture.draw(tl + offset, Arg::top(ColorF(1, 1)), Arg::bottom(ColorF(1, 0)));
    }

}
