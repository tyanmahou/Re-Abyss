#include "AtlantisVM.hpp"

#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <Siv3D.hpp>

namespace abyss::Cycle::Title::BackGround
{
    AtlantisVM::AtlantisVM() :
        m_texture(ResourceManager::Main()->loadTexture(U"cycle/title/atlantis.png"))
    {}

    void AtlantisVM::draw() const
    {
        m_texture.drawAt(m_pos);
    }
}
