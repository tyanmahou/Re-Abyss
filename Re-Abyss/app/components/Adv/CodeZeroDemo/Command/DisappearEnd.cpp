#include <abyss/components/Adv/CodeZeroDemo/Command/DisappearEnd.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    DisappearEnd::DisappearEnd(AdvObj* pObj) :
        m_pObj(pObj)
    {
    }
    void DisappearEnd::onStart()
    {
        m_pObj->find<TalkCtrl>()->resume();
        m_pObj->getModule<UIs>()->setFilter(UI::Filter::Always);
    }
    Coro::Fiber<> DisappearEnd::onCommand()
    {
        co_return;
    }
}
