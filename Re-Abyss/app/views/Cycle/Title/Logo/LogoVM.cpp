#include "LogoVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Cycle::Title::Logo
{
    LogoVM::LogoVM():
        m_texture(Resource::Assets::Main()->loadTexture(U"cycle/title/logo.png"))
    {}
    void LogoVM::draw() const
    {
        m_texture.drawAt(m_pos, ColorF(1.0, m_alpha));
    }

}
