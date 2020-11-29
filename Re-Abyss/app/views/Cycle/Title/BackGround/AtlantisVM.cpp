#include "AtlantisVM.hpp"

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Cycle::Title::BackGround
{
    AtlantisVM::AtlantisVM() :
        m_texture(Resource::Assets::Main()->loadTexture(U"cycle/title/atlantis.png"))
    {}

    void AtlantisVM::draw() const
    {
        m_texture.drawAt(m_pos);
    }
}
