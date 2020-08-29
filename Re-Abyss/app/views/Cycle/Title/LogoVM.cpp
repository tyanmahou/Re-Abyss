#include "LogoVM.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <Siv3D.hpp>

namespace abyss::Cycle::Title::Logo
{
    LogoVM::LogoVM():
        m_texture(ResourceManager::Main()->loadTexture(U"cycle/title/logo.png"))
    {}
    void LogoVM::draw() const
    {
        const auto alpha = Math::Saturate(Periodic::Triangle0_1(1s, m_time0_1) * (1 / 0.75));

        m_texture.drawAt(m_pos, ColorF(1.0, alpha));
    }

}
