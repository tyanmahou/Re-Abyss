#include "EraseUserConfirm.hpp"
#include <abyss/commons/FontName.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    EraseUserConfirm::EraseUserConfirm(std::function<void()> callback) :
        m_callback(callback),
        m_cursor(std::make_unique<UI::Serif::CursorVM>())
    {}
    bool EraseUserConfirm::update()
    {
        if (InputManager::Up.down()) {
            m_yes = true;
        }
        if (InputManager::Down.down()) {
            m_yes = false;
        }
        if (InputManager::A.down()) {
            if (m_yes) {
                m_callback();
            }
            return false;
        }
        return !InputManager::B.down();
    }
    void EraseUserConfirm::draw() const
    {
        const auto board = Param::Confirm::Board();
        board.draw(Palette::Black);

        auto msgPos = board.center() + Param::Confirm::MessagePos;
        FontAsset(FontName::UserInfo)(U"本当に削除しますか？").drawAt(msgPos);

        auto choicePos = board.center() + Param::Confirm::ChoiceBasePos;
        FontAsset(FontName::UserInfo)(U"はい").drawAt(choicePos);
        FontAsset(FontName::UserInfo)(U"いいえ").drawAt(choicePos + Vec2{ 0, Param::Confirm::ChoiceOffset });

        {
            Vec2 pos = choicePos +
                Vec2{
                Param::Confirm::CursorOffset,
                m_yes ? 0 : Param::Confirm::ChoiceOffset
            };

            m_cursor->setVertical(false)
                .setPos(pos)
                .draw();
        }
    }
}
