#include <abyss/components/Novel/CodeZeroDemo/Command/AppearEnd.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Novel/Common/TalkCtrl.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/components/Event/CreateBossHPBar/Builder.hpp>
#include <abyss/components/Event/CreateBossHPBar/MainStream.hpp>
#include <abyss/components/UI/BossHPBar/Builder.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    AppearEnd::AppearEnd(TalkObj* pTalk):
        m_pTalk(pTalk)
    {
    }
    void AppearEnd::onStart()
    {
        m_pTalk->find<TalkCtrl>()->resume();
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Always);

        auto world = m_pTalk->getModule<World>();
        if (auto codeZero = world->find<Actor::Enemy::CodeZero::CodeZeroProxy>()) {
            auto hpBar = m_pTalk->getModule<UIs>()->create<UI::BossHPBar::Builder>(codeZero->getActor());
            // HPチャージ
            auto chargeHpBar = m_pTalk->getModule<Events>()->create<Event::CreateBossHPBar::Builder>(hpBar);
            chargeHpBar->find<Event::CreateBossHPBar::MainStream>()
                ->setBossBgmPath(U"bgm/Main/Stage0/stage0_boss.aas");
        }
    }
    Coro::Fiber<> AppearEnd::onCommand()
    {
        co_return;
    }
}
