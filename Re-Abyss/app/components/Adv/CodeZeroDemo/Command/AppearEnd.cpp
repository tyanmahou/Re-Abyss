#include <abyss/components/Adv/CodeZeroDemo/Command/AppearEnd.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    AppearEnd::AppearEnd(AdvObj* pObj):
        m_pObj(pObj)
    {
    }
    void AppearEnd::onStart()
    {
        m_pObj->find<TalkCtrl>()->resume();
        m_pObj->getModule<UIs>()->setFilter(UI::Filter::Always);
    }
    Coro::Fiber<> AppearEnd::onCommand()
    {
        co_return;
    }
}
