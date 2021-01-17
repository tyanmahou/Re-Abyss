#include "PlayerInfoVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/util/MaskUtil/MaskUtil.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/params/UI/PlayerInfo/Param.hpp>
#include <Siv3D.hpp>
namespace abyss::ui::PlayerInfo
{
    PlayerInfoVM::PlayerInfoVM() :
        m_texture(Resource::Assets::Main()->loadTexturePacker(U"ui/PlayerInfo/player_info.json"))
    {}

    void PlayerInfoVM::draw()const
    {
        // Face
        {
            auto mask = MaskUtil::Instance().equal([&]() {
                m_texture(U"face_mask").draw(m_pos);
            });
            if (m_face.texture) {
                m_face.drawAt(m_pos + Param::Face::BasePos);
            }
        }
        m_texture(U"face_frame").draw(m_pos);

        // HP
        {

        }

        // Ooparts
        {
            if(m_ooparts.texture) {
                ScopedColorAdd2D scoped(Palette::White);

                m_ooparts.draw(m_pos + Param::Ooparts::BasePos);
            }

            FontAsset(FontName::PlayerInfoOopartsName)(m_oopartsName)
                .draw(m_pos + Param::Ooparts::BasePos);
        }
    }
}
