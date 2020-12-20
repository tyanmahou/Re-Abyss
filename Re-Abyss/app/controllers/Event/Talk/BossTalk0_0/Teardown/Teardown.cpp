#include "Teardown.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Demo/DemoActor.hpp>
#include <abyss/controllers/Event/Talk/Common/CreateBossHPBar/ChargeBossHPBar.hpp>

#include <abyss/controllers/UI/UI.hpp>
#include <abyss/controllers/UI/BossHPBar/BossHPBar.hpp>

#include <abyss/components/Actors/Enemy/CodeZero/CodeZeroProxy.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    void Teardown::onStart()
    {
        auto world = m_pManager->getModule<World>();
       
        if (auto demoCodeZero = world->find<Actor::Enemy::CodeZero::Demo::DemoActor>()) {
            demoCodeZero->destroy();
        }
        if (auto codeZero = world->find<Actor::Enemy::CodeZero::CodeZeroProxy>()) {
            codeZero->setActive(true);
            auto hpBar = m_pManager->getModule<UI>()->create<ui::BossHPBar>(codeZero->getActor());
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
