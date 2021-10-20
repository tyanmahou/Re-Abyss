//#include "OldMain.hpp"
//#include <abyss/modules/UI/base/UIObj.hpp>
//#include <abyss/modules/Novel/base/TalkObj.hpp>
//
//#include <abyss/components/Novel/Common/Serif/OldSerifCtrl.hpp>
//
//#include <abyss/views/UI/Serif/MessageVM.hpp>
//#include <abyss/views/UI/Serif/MessageBoxVM.hpp>
//#include <abyss/views/UI/Serif/CursorVM.hpp>
//#include <abyss/views/util/Pivot/PivotUtil.hpp>
//#include <abyss/commons/Constants.hpp>
//
//#include <Siv3D.hpp>
//
//namespace abyss::UI::Serif
//{
//    OldMain::OldMain(
//        UIObj* pUi,
//        const Ref<Novel::OldSerifCtrl>& serif
//    ) :
//        m_pUi(pUi),
//        m_serif(serif),
//        m_messageView(std::make_unique<MessageVM>()),
//        m_boxView(std::make_unique<MessageBoxVM>()),
//        m_cursorView(std::make_unique<CursorVM>())
//    {}
//
//    void OldMain::onStart()
//    {
//    }
//
//    void OldMain::onUpdate()
//    {
//        if (!m_serif) {
//            m_pUi->destroy();
//            return;
//        }
//    }
//
//    void OldMain::onDraw() const
//    {
//        if (!m_serif || m_serif->isEnd()) {
//            return;
//        }
//        const Vec2 pos = PivotUtil::FromTc(0, 150);
//        m_boxView
//            ->setIsLeft(m_serif->isLeft())
//            .setPos(pos)
//            .setName(m_serif->getActorName());
//
//        //if (const auto& actorName = m_serif->getActorName(); m_faceTable && actorName) {
//        //    const auto& faceKind = m_serif->getCurrentKind();
//        //    if (m_faceTable->isContain(*actorName, faceKind)) {
//        //        m_boxView->setFaceIcon(m_faceTable->getFace(*actorName, faceKind));
//        //    }
//        //}
//        m_boxView->draw();
//
//        const double messagePosX = m_serif->isLeft() ? -180 : -340;
//        m_messageView
//            ->setStrIndex(m_serif->getStrIndex())
//            .setCurrent(m_serif->getCurrent())
//            .setPrev(m_serif->getPrev())
//            .setPos(pos + s3d::Vec2{ messagePosX, -25 })
//            .draw()
//            ;
//
//        if (m_serif->isAll()) {
//            m_cursorView->setPos(pos + s3d::Vec2{ messagePosX + 500, 50 }).draw();
//        }
//    }
//
//}
