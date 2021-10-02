#include "PlayerInfoExVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::PlayerInfo
{
    PlayerInfoExVM::PlayerInfoExVM():
        m_face(Resource::Assets::Main()->load(U"actors/Player/face.json"))
    {

    }
    PlayerInfoExVM& PlayerInfoExVM::setFace(const s3d::String& faceName)
    {
        PlayerInfoVM::setFace(m_face(faceName).scaled(0.8));
        return *this;
    }
    PlayerInfoExVM& PlayerInfoExVM::setOoparts(OopartsType ooparts)
    {
        if (ooparts == OopartsType::Invalid) {
            PlayerInfoVM::setOoparts(s3d::TextureRegion(), U"");
        } else {
            PlayerInfoVM::setOoparts(m_icons(ooparts), Enum::ToStr(ooparts).uppercase());
        }
        return *this;
    }
}