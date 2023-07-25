#include <abyss/components/Adv/BossCommon/Command/BossArrival.hpp>

#include <abyss/components/UI/BossArrival/Builder.hpp>
#include <abyss/components/UI/BossArrival/Main.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/UI/UIs.hpp>

namespace abyss::Adv::BossCommon
{
    BossArrival::BossArrival(AdvObj* pObj):
        m_pObj(pObj)
    {
    }
    void BossArrival::onStart()
    {
        m_prevUiFilter = m_pObj->getModule<UIs>()->getFilter();
        // UIレイヤーを変更
        m_pObj->getModule<UIs>()->setFilter(UI::Filter::Event);

        auto uiObj = m_pObj->getModule<UIs>()->create<UI::BossArrival::Builder>();
        m_main = uiObj->find<UI::BossArrival::Main>();
    }
    void BossArrival::onEnd()
    {
        // UIレイヤーを戻す
        m_pObj->getModule<UIs>()->setFilter(m_prevUiFilter);
    }
    Coro::Fiber<> BossArrival::onCommand()
    {
        while(m_main) {
            co_yield{};
        }
        co_return;
    }
}
