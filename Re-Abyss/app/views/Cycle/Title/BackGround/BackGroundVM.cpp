#include "BackGroundVM.hpp"

#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <Siv3D.hpp>

namespace abyss::Cycle::Title::BackGround
{
    BackGroundVM::BackGroundVM() :
        m_texture(ResourceManager::Main()->loadTexture(U"cycle/title/bg.png"))
    {}

    void BackGroundVM::draw() const
    {
        m_texture.drawAt(m_pos, ColorF(1, Periodic::Sine0_1(5s) * 0.3 + 0.7));
    }
}
