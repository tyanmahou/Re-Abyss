#include "Teardown.hpp"
#include <abyss/modules/System/System.hpp>
#include <abyss/modules/Event/Talk/Common/CreateBossHPBar/ChargeBossHPBar.hpp>

#include <abyss/modules/UI/UI.hpp>

#include <abyss/components/Actors/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Demo/DemoCtrl.hpp>
#include <abyss/components/UI/BossHPBar/Builder.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    void Teardown::onStart()
    {
        auto world = m_pManager->getModule<World>();
       
        if (auto demoCodeZero = world->find<Actor::Enemy::CodeZero::Demo::DemoCtrl>()) {
            demoCodeZero->destroy();
        }
        if (auto codeZero = world->find<Actor::Enemy::CodeZero::CodeZeroProxy>()) {
            codeZero->setActive(true);
            auto hpBar = m_pManager->getModule<UI>()->create<ui::BossHPBar::Builder>(codeZero->getActor());
            // HPチャージ
            auto chargeHpBar = std::make_shared<ChargeBossHPBar>(hpBar);
            chargeHpBar->setBossBgmPath(U"bgm/stage/stage0/stage0_boss.aas");
            m_pManager->getModule<Events>()->regist(chargeHpBar);
        }
    }

    bool Teardown::update([[maybe_unused]]double dt)
    {
        return false;
    }

}
