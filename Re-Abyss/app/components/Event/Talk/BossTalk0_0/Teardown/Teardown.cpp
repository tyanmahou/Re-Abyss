#include "Teardown.hpp"

#include <abyss/modules/Event/Talk/TalkObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Demo/DemoCtrl.hpp>
#include <abyss/components/Event/CreateBossHPBar/Builder.hpp>
#include <abyss/components/Event/CreateBossHPBar/MainStream.hpp>
#include <abyss/components/UI/BossHPBar/Builder.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    Teardown::Teardown(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {}

    void Teardown::onStart()
    {
        auto world = m_pTalk->getModule<World>();

        if (auto demoCodeZero = world->find<Actor::Enemy::CodeZero::Demo::DemoCtrl>()) {
            demoCodeZero->destroy();
        }
        if (auto codeZero = world->find<Actor::Enemy::CodeZero::CodeZeroProxy>()) {
            codeZero->setActive(true);
            auto hpBar = m_pTalk->getModule<UIs>()->create<UI::BossHPBar::Builder>(codeZero->getActor());
            // HPチャージ
            auto chargeHpBar = m_pTalk->getModule<Events>()->create<CreateBossHPBar::Builder>(hpBar);
            chargeHpBar->find<CreateBossHPBar::MainStream>()
                ->setBossBgmPath(U"bgm/stage/stage0/stage0_boss.aas");
        }
    }

    Coro::Task<> Teardown::onTalk()
    {
        co_return;
    }
}