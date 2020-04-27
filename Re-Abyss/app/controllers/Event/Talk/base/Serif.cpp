#include "Serif.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Event/Talk/MessageVM.hpp>
#include <abyss/views/Event/Talk/MessageBoxVM.hpp>
#include <abyss/views/Event/Talk/CursorVM.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/controllers/Event/Talk/base/FaceManager.hpp>

namespace abyss::Event::Talk
{
    Serif::Serif():
        m_messageView(std::make_shared<MessageVM>()),
        m_boxView(std::make_shared<MessageBoxVM>()),
        m_cursorView(std::make_shared<CursorVM>())
    {}
    Serif::~Serif()
    {}
    void Serif::setModel(SerifModel && model)
    {
        m_serif = std::move(model);
    }
    void Serif::setFaceManager(const std::shared_ptr<FaceManager>& faceManager)
    {
        m_faceManager = faceManager;
    }
    bool Serif::update()
    {
        return m_serif.update();
    }
    void Serif::draw() const
    {
        if (m_serif.isEnd()) {
            return;
        }
        const Vec2 pos = { Constants::GameScreenSize.x / 2.0f, 150 };
        m_boxView
            ->setIsLeft(m_serif.isLeft())
            .setPos(pos)
            .setName(m_serif.getActorName());

        if (const auto& actorName = m_serif.getActorName(); m_faceManager && actorName) {
            auto faceKind = m_serif.getKind().value_or(U"default");
            if (m_faceManager->isContain(*actorName, faceKind)) {
                m_boxView->setFaceIcon(m_faceManager->getFace(*actorName, faceKind));
            }
        }
        m_boxView->draw();

        const double messagePosX = m_serif.isLeft() ? 300 : 140;
        m_messageView
            ->setStrIndex(m_serif.getStrIndex())
            .setCurrent(m_serif.getCurrentView())
            .setPrev(m_serif.getPrevView())
            .setPos({ messagePosX, 125 })
            .draw()
        ;

        if (m_serif.isAll()) {
            m_cursorView->setPos({ messagePosX + 500, 200 }).draw();
        }
    }
}
