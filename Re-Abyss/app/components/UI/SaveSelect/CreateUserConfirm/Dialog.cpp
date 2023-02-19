#include <abyss/components/UI/SaveSelect/CreateUserConfirm/Dialog.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/MsgUtil.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::CreateUserConfirm
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
            m_playMode = UserPlayMode::Normal;
        }
        if (InputManager::Down.down()) {
            m_playMode = UserPlayMode::Hard;
        }
        if (InputManager::A.down()) {
            DialogResult::set(Result{
                .isBack = false,
                .playMode = m_playMode
            });
            return;
        } else if (InputManager::B.down()) {
            DialogResult::set(Result{
                .isBack = true,
                .playMode = m_playMode
            });
        }
    }
    void Dialog::onDraw() const
    {
        const auto board = Param::Confirm::Board();
        board.draw(Palette::Black);

        auto msgPos = board.center() + Param::Confirm::MessagePos;
        FontAsset(FontName::UserInfo)(MsgUtil::SaveSlect_CreateUser_Title).drawAt(msgPos);

        auto choicePos = board.center() + Param::Confirm::ChoiceBasePos;
        FontAsset(FontName::UserInfo)(MsgUtil::Name(UserPlayMode::Normal)).drawAt(choicePos);
        FontAsset(FontName::UserInfo)(MsgUtil::Name(UserPlayMode::Hard)).drawAt(choicePos + Vec2{ 0, Param::Confirm::ChoiceOffset });

        {
            Vec2 pos = choicePos +
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
