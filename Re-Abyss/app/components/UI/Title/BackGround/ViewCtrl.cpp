#include <abyss/components/UI/Title/BackGround/ViewCtrl.hpp>

#include <abyss/components/UI/Title/BackGround/BgCtrl.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/views/UI/Title/BackGround/BackGroundVM.hpp>
#include <abyss/views/UI/Title/BackGround/AtlantisVM.hpp>

#include <Siv3D.hpp>

namespace abyss::UI::Title::BackGround
{
    ViewCtrl::ViewCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_bgView(std::make_unique<BackGroundVM>()),
        m_atlantisView(std::make_unique<AtlantisVM>())
    {
    }

    ViewCtrl::~ViewCtrl()
    {}

    void ViewCtrl::setup(Executer executer)
    {
        executer.onStart().addAfter<BgCtrl>();
    }
    void ViewCtrl::onStart()
    {
        m_bgCtrl = m_pUi->find<BgCtrl>();
    }
    void ViewCtrl::onDraw() const
    {
        m_bgView
            ->setPos(m_bgCtrl->getPos())
            .draw();
        m_atlantisView
            ->setPos(m_bgCtrl->getAtlantisPos())
            .draw();
    }
}
