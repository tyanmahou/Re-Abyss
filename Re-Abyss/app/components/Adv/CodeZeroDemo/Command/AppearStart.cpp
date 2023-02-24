#include <abyss/components/Adv/CodeZeroDemo/Command/AppearStart.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    AppearStart::AppearStart(AdvObj* pObj) :
        m_pObj(pObj)
    {
    }
    void AppearStart::onStart()
    {
        m_pObj->find<TalkCtrl>()->request();
        m_pObj->getModule<UIs>()->setFilter(UI::Filter::Adv);
    }
    Coro::Fiber<> AppearStart::onCommand()
    {
        co_return;
    }
}
