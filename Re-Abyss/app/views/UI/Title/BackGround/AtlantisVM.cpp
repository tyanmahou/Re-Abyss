#include "AtlantisVM.hpp"

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Title::BackGround
{
    AtlantisVM::AtlantisVM() :
        m_texture(Resource::Assets::Main()->loadTexture(U"ui/Title/atlantis.png"))
    {}

    void AtlantisVM::draw() const
    {
        m_texture.drawAt(m_pos);
    }
}