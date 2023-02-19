#include <abyss/components/UI/SaveSelect/EraseUserConfirm/Dialog.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Msg/Manager.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::EraseUserConfirm
{
    void Dialog::Build(UIObj* pUi)
    {
        pUi->attach<Dialog>(pUi)
            ->setOrder(DrawOrder::UI::Dialog);
    }

    Dialog::Dialog(UIObj* pUi):
        m_pUi(pUi),
        m_cursor(std::make_unique<UI::Message::CursorVM>())
    {}
    void Dialog::onUpdate()
    {
        if (InputManager::Up.down()) {
            m_yes = true;
        }
        if (InputManager::Down.down()) {
            m_yes = false;
        }
        if (InputManager::A.down()) {
            DialogResult::set(Result{
                .yes = m_yes
            });
            return;
        } else if (InputManager::B.down()) {
            DialogResult::set(Result{
                .yes = false
            });
        }
    }
    void Dialog::onDraw() const
    {
        const auto board = Param::Confirm::Board();
        board.draw(Palette::Black);

        auto msgPos = board.center() + Param::Confirm::MessagePos;
        FontAsset(FontName::UserInfo)(Msg::Text(U"SaveSelect", U"EraseUser_Title")).drawAt(msgPos);

        auto choicePos = board.center() + Param::Confirm::ChoiceBasePos;
        FontAsset(FontName::UserInfo)(Msg::Text(U"Common", U"Yes")).drawAt(choicePos);
        FontAsset(FontName::UserInfo)(Msg::Text(U"Common", U"No")).drawAt(choicePos + Vec2{ 0, Param::Confirm::ChoiceOffset });

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
