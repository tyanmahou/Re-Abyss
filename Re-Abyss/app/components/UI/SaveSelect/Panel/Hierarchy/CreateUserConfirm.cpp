#include "CreateUserConfirm.hpp"

#include <abyss/commons/FontName.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    CreateUserConfirm::CreateUserConfirm(std::function<void(UserPlayMode)> callback) :
        m_callback(callback),
        m_cursor(std::make_unique<UI::Serif::CursorVM>())
    {}

    bool CreateUserConfirm::update()
    {
        if (InputManager::Up.down()) {
            m_playMode = UserPlayMode::Normal;
        }
        if (InputManager::Down.down()) {
            m_playMode = UserPlayMode::Hard;
        }
        if (InputManager::A.down()) {
            m_callback(m_playMode);
            m_isDone = true;
        }
        return m_isDone || !InputManager::B.down();
    }

    void CreateUserConfirm::draw() const
    {
        if (m_isDone) {
            return;
        }
        Param::Confirm::Board().draw(Palette::Black);

        FontAsset(FontName::UserInfo)(U"難易度をえらんでください").drawAt(Param::Confirm::MessagePos);

        FontAsset(FontName::UserInfo)(U"ノーマルモード").drawAt(Param::Confirm::ChoiceBasePos);
        FontAsset(FontName::UserInfo)(U"ハードモード").drawAt(Param::Confirm::ChoiceBasePos + Vec2{ 0, Param::Confirm::ChoiceOffset });

        {
            Vec2 pos = Param::Confirm::ChoiceBasePos +
                Vec2{
                Param::Confirm::CursorOffset,
                m_playMode == UserPlayMode::Normal ? 0 : Param::Confirm::ChoiceOffset
            };

            m_cursor->setVertical(false)
                .setPos(pos)
                .draw();
        }
    }

}
