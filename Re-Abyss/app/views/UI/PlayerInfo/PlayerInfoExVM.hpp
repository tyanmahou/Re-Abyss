#pragma once
#include <abyss/views/UI/PlayerInfo/PlayerInfoVM.hpp>
#include <abyss/types/OopartsType.hpp>
#include <abyss/views/actors/Ooparts/base/OopartsVM.hpp>

namespace abyss::ui::PlayerInfo
{
    class PlayerInfoExVM : public PlayerInfoVM
    {
        TexturePacker m_face;
    public:
        PlayerInfoExVM();

        PlayerInfoExVM& setFace(const s3d::String& faceName);

        PlayerInfoExVM& setOoparts(OopartsType ooparts);
    };
}