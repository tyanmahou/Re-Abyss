#include "Main.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/modules/Event/Talk/TalkObj.hpp>

#include <abyss/components/Events/Talk/Common/Serif/SerifCtrl.hpp>
#include <abyss/components/Events/Talk/Common/Serif/FaceTable.hpp>

#include <abyss/views/UI/Serif/MessageVM.hpp>
#include <abyss/views/UI/Serif/MessageBoxVM.hpp>
#include <abyss/views/UI/Serif/CursorVM.hpp>
#include <abyss/commons/Constants.hpp>

#include <Siv3D.hpp>

namespace abyss::ui::Serif
{
    Main::Main(IUserInterface* pUi, Event::Talk::TalkObj* pTalk) :
        m_pUi(pUi),
        m_pTalk(pTalk),
        m_messageView(std::make_unique<MessageVM>()),
        m_boxView(std::make_unique<MessageBoxVM>()),
        m_cursorView(std::make_unique<CursorVM>())
    {}

    void Main::onStart()
    {
        m_serif = m_pTalk->find<Event::Talk::SerifCtrl>();
        m_faceTable = m_pTalk->find<Event::Talk::FaceTable>();
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
