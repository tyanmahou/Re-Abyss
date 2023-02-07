#include <abyss/views/UI/PlayerInfo/PlayerInfoVM.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/params/UI/PlayerInfo/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::PlayerInfo
{
    PlayerInfoVM::PlayerInfoVM() :
        m_texture(Resource::Assets::Main()->load(U"UI/PlayerInfo/PlayerInfo.json")),
        m_shader(Constants::AppResolution)
    {}

    void PlayerInfoVM::draw()const
    {
        // Face
        {
            m_texture(U"face_mask").draw(m_pos);
            auto mask = m_shader.equal([&]() {
                m_texture(U"face_mask").draw(m_pos);
            });
            if (m_face.texture) {
                m_face.resized(Param::Face::Size).drawAt(m_pos + Param::Face::BasePos);
            }
        }
        // Base
        m_texture(U"base").draw(m_pos);

        // HP
        {
            for (int32 hp : step(1, m_maxHp)) {
                m_texture(U"hp_gauge_base").draw(m_pos + Param::HP::BasePos + Vec2{ (hp - 1) * Param::HP::Offset, 0});
            }
            for (int32 hp : step(1, m_hp)) {
                m_texture(U"hp_gauge").draw(m_pos + Param::HP::BasePos + Vec2{ (hp - 1) * Param::HP::Offset, 0 });
            }
        }

        // Ooparts
        {
            if(m_ooparts.texture) {
                ScopedColorAdd2D scoped(ColorF(1.0, 0.0));

                m_ooparts.draw(m_pos + Param::Ooparts::BasePos);
            }

            FontAsset(FontName::PlayerInfoOopartsName)(m_oopartsName)
                .draw(m_pos + Param::Ooparts::NamePos);
        }
    }
}
