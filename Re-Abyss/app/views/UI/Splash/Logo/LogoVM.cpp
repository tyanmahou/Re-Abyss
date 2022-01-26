#include <abyss/views/UI/Splash/Logo/LogoVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Splash::Logo
{
    LogoVM::LogoVM():
        m_texture(Resource::Assets::Main()->load(U"ui/Splash/logo.png"))
    {}
    void LogoVM::draw() const
    {
        const auto alpha = Math::Saturate(Periodic::Triangle0_1(1s, m_time0_1) * (1 / 0.75));

        m_texture.drawAt(m_pos, ColorF(1.0, alpha));
    }

}
