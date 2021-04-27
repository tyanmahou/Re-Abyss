#pragma once
#include <abyss/views/UI/PlayerInfo/PlayerInfoVM.hpp>
#include <abyss/types/OopartsType.hpp>
#include <abyss/views/actors/Ooparts/base/IconView.hpp>

namespace abyss::UI::PlayerInfo
{
    class PlayerInfoExVM : public PlayerInfoVM
    {
        TexturePacker m_face;
        Actor::Ooparts::IconView m_icons;
    public:
        PlayerInfoExVM();

        PlayerInfoExVM& setFace(const s3d::String& faceName);

        PlayerInfoExVM& setOoparts(OopartsType ooparts);
    };
}