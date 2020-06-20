#include "Serif.hpp"
#include <Siv3D.hpp>

#include <abyss/commons/Constants.hpp>

#include <abyss/models/Event/Talk/SerifModel.hpp>

#include <abyss/views/UI/Serif/MessageVM.hpp>
#include <abyss/views/UI/Serif/MessageBoxVM.hpp>
#include <abyss/views/UI/Serif/CursorVM.hpp>

namespace abyss::ui
{
    Serif::Serif(const Ref<Event::Talk::SerifModel>& serif):
        m_serif(serif),
        m_messageView(std::make_unique<MessageVM>()),
        m_boxView(std::make_unique<MessageBoxVM>()),
        m_cursorView(std::make_unique<CursorVM>())
    {

    }

    void Serif::update([[maybe_unused]] double dt)
    {
        if (!m_serif) {
            this->destroy();
            return;
        }
    }

    void Serif::draw() const
    {
        //if (!m_serif || m_serif->isEnd()) {
        //    return;
        //}
        //const Vec2 pos = { Constants::GameScreenSize.x / 2.0f, 150 };
        //m_boxView
        //    ->setIsLeft(m_serif->isLeft())
        //    .setPos(pos)
        //    .setName(m_serif->getActorName());

        //if (const auto& actorName = m_serif->getActorName(); m_faceManager && actorName) {
        //    auto faceKind = m_serif->getKind().value_or(U"default");
        //    if (m_faceManager->isContain(*actorName, faceKind)) {
        //        m_boxView->setFaceIcon(m_faceManager->getFace(*actorName, faceKind));
        //    }
        //}
        //m_boxView->draw();

        //const double messagePosX = m_serif->isLeft() ? 300 : 140;
        //m_messageView
        //    ->setStrIndex(m_serif->getStrIndex())
        //    .setCurrent(m_serif->getCurrent())
        //    .setPrev(m_serif->getPrev())
        //    .setPos({ messagePosX, 125 })
        //    .draw()
        //    ;

        //if (m_serif->isAll()) {
        //    m_cursorView->setPos({ messagePosX + 500, 200 }).draw();
        //}
    }
}