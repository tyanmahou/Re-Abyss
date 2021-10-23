#include "Main.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>

#include <abyss/components/Novel/base/Engine.hpp>

#include <abyss/views/UI/Serif/MessageVM.hpp>
#include <abyss/views/UI/Serif/MessageBoxVM.hpp>
#include <abyss/views/UI/Serif/CursorVM.hpp>
#include <abyss/views/util/Pivot/PivotUtil.hpp>
#include <abyss/commons/Constants.hpp>

#include <Siv3D.hpp>

namespace abyss::UI::Serif
{
    Main::Main(
        UIObj* pUi,
        const Ref<Novel::Engine>& engine
    ) :
        m_pUi(pUi),
        m_engine(engine),
        m_messageView(std::make_unique<MessageVM>()),
        m_boxView(std::make_unique<MessageBoxVM>()),
        m_cursorView(std::make_unique<CursorVM>())
    {}

    void Main::onStart()
    {}

    void Main::onUpdate()
    {
        if (!m_engine) {
            m_pUi->destroy();
            return;
        }
    }

    void Main::onDraw() const
    {
        if (!m_engine) {
            return;
        }
        const auto& serif = m_engine->getSerif();

        const Vec2 pos = PivotUtil::FromTc(0, 150);
        m_boxView
            ->setIsLeft(serif.isLeft())
            .setPos(pos)
            .setName(serif.getName());

        //if (const auto& actorName = m_serif->getActorName(); m_faceTable && actorName) {
        //    const auto& faceKind = m_serif->getCurrentKind();
        //    if (m_faceTable->isContain(*actorName, faceKind)) {
        //        m_boxView->setFaceIcon(m_faceTable->getFace(*actorName, faceKind));
        //    }
        //}
        m_boxView->draw();

        const double messagePosX = serif.isLeft() ? -180 : -340;
        //m_messageView
        //    ->setStrIndex(m_serif->getStrIndex())
        //    .setCurrent(m_serif->getCurrent())
        //    .setPrev(m_serif->getPrev())
        //    .setPos(pos + s3d::Vec2{ messagePosX, -25 })
        //    .draw()
        //    ;

        if (m_engine->isInputWait()) {
            m_cursorView->setPos(pos + s3d::Vec2{ messagePosX + 500, 50 }).draw();
        }
    }
}