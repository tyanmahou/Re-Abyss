#include "Main.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Event/Talk/TalkObj.hpp>

#include <abyss/components/Event/Talk/Common/Serif/SerifCtrl.hpp>
#include <abyss/components/Event/Talk/Common/Serif/FaceTable.hpp>

#include <abyss/views/UI/Serif/MessageVM.hpp>
#include <abyss/views/UI/Serif/MessageBoxVM.hpp>
#include <abyss/views/UI/Serif/CursorVM.hpp>
#include <abyss/commons/Constants.hpp>

#include <Siv3D.hpp>

namespace abyss::UI::Serif
{
    Main::Main(
        UIObj* pUi,
        const Ref<Event::Talk::SerifCtrl>& serif,
        const Ref<Event::Talk::FaceTable>& faceTable
    ) :
        m_pUi(pUi),
        m_serif(serif),
        m_faceTable(faceTable),
        m_messageView(std::make_unique<MessageVM>()),
        m_boxView(std::make_unique<MessageBoxVM>()),
        m_cursorView(std::make_unique<CursorVM>())
    {}

    void Main::onStart()
    {
    }

    void Main::onUpdate()
    {
        if (!m_serif) {
            m_pUi->destroy();
            return;
        }
    }

    void Main::onDraw() const
    {
        if (!m_serif || m_serif->isEnd()) {
            return;
        }
        const Vec2 pos = { Constants::GameScreenSize.x / 2.0f, 150 };
        m_boxView
            ->setIsLeft(m_serif->isLeft())
            .setPos(pos)
            .setName(m_serif->getActorName());

        if (const auto& actorName = m_serif->getActorName(); m_faceTable && actorName) {
            const auto& faceKind = m_serif->getCurrentKind();
            if (m_faceTable->isContain(*actorName, faceKind)) {
                m_boxView->setFaceIcon(m_faceTable->getFace(*actorName, faceKind));
            }
        }
        m_boxView->draw();

        const double messagePosX = m_serif->isLeft() ? 300 : 140;
        m_messageView
            ->setStrIndex(m_serif->getStrIndex())
            .setCurrent(m_serif->getCurrent())
            .setPrev(m_serif->getPrev())
            .setPos({ messagePosX, 125 })
            .draw()
            ;

        if (m_serif->isAll()) {
            m_cursorView->setPos({ messagePosX + 500, 200 }).draw();
        }
    }

}
