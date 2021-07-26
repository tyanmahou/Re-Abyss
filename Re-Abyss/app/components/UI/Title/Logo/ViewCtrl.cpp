#include "ViewCtrl.hpp"
#include "LogoCtrl.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/views/UI/Title/Logo/LogoVM.hpp>

#include <Siv3D.hpp>

namespace abyss::UI::Title::Logo
{
    ViewCtrl::ViewCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<LogoVM>())
    {
    }

    ViewCtrl::~ViewCtrl()
    {}

    void ViewCtrl::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<LogoCtrl>();
    }
    void ViewCtrl::onStart()
    {
        m_logoCtrl = m_pUi->find<LogoCtrl>();
    }
    void ViewCtrl::onDraw() const
    {
        auto [view1, view2] = m_logoCtrl->getViewParams();

        if (view1) {
            m_view
                ->setPos(view1->pos)
                .setAlpha(view1->alpha)
                .draw();
        }
        if (view2) {
            m_view
                ->setPos(view2->pos)
                .setAlpha(view2->alpha)
                .draw();
        }
    }
}
