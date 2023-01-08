#include <abyss/views/FieldEnv/Sky/SkyView.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/Camera/CameraView.hpp>

namespace abyss::FieldEnv
{
    SkyView::SkyView() :
        m_texture(Resource::Assets::Main()->load(U"Env/Sky.png")),
        m_texture2(Resource::Assets::Main()->load(U"Env/Caustics.png"))
    {

    }

    SkyView& SkyView::setTime(double time)
    {
        m_skyShader.setTime(time);
        return *this;
    }

    void SkyView::draw(const s3d::Vec2& pos) const
    {
        Graphics2D::SetPSTexture(1, m_texture2);
        ScopedRenderStates2D blend(BlendState::Additive, SamplerState::MirrorNearest);
        auto shader = m_skyShader.start();
        auto offset = Vec2{ 0, s3d::Min(0.0, -pos.y / 20.0) };
        m_texture.draw(pos + offset, Arg::top(ColorF(1, 1)), Arg::bottom(ColorF(1, 0)));
    }

}
