#include <abyss/views/UI/Title/Logo/LogoVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Title::Logo
{
    LogoVM::LogoVM():
        m_texture(Resource::Assets::Main()->load(U"UI/Title/Logo.png"))
    {}
    void LogoVM::draw() const
    {
        m_texture.drawAt(m_pos, ColorF(1.0, m_alpha));
    }

}
