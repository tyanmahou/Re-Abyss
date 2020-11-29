#include "SkyView.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/Camera/CameraView.hpp>
namespace abyss
{
    SkyView::SkyView() :
        m_texture(Resource::Assets::Main()->loadTexture(U"bgs/sky.png")),
        m_texture2(Resource::Assets::Main()->loadTexture(U"bgs/surface.png"))
    {

    }

    SkyView& SkyView::setTime(double time)
    {
        m_skyShader.setTime(time);
        return *this;
    }

    void SkyView::draw(const CameraView& camera) const
    {
        Graphics2D::SetTexture(1, m_texture2);
        ScopedRenderStates2D blend(BlendState::Additive, SamplerState::MirrorNearest);
        auto shader = m_skyShader.start();
        auto tl = camera.screenRegion().tl();
        auto offset = Vec2{ 0, -tl.y / 20.0 };
        m_texture.draw(tl + offset, Arg::top(ColorF(1, 1)), Arg::bottom(ColorF(1, 0)));
    }

}
