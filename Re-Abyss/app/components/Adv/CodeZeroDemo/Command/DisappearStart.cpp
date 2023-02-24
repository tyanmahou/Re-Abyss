#include <abyss/components/Adv/CodeZeroDemo/Command/DisappearStart.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    DisappearStart::DisappearStart(AdvObj* pObj) :
        m_pObj(pObj)
    {
    }
    void DisappearStart::onStart()
    {
        m_pObj->find<TalkCtrl>()->request();
        m_pObj->getModule<UIs>()->setFilter(UI::Filter::Adv);
    }
    Coro::Fiber<> DisappearStart::onCommand()
    {
        co_return;
    }
}
