#include "ViewCtrl.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::SaveSelect::UserInfo
{
    ViewCtrl::ViewCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<UserInfo::UserInfoView>())
    {}

    void ViewCtrl::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<Main::UserSelector>();
    }
    void ViewCtrl::onStart()
    {
        m_selector = m_pUi->find<Main::UserSelector>();
        m_kiraKira = m_pUi->find<KiraKiraCtrl>();
    }

    void ViewCtrl::onUpdate()
    {
        m_time += m_pUi->deltaTime();
        m_view->setTime(m_time);

        m_kiraKira
            ->setPos(m_view->getPlayerView()->getOopartsPos())
            .setActive(m_selector->isValidUser());
    }

    void ViewCtrl::onDraw() const
    {
        if (auto&& user = m_selector->getSelectUser()) {
            m_view->draw(*user);
        }
    }
}