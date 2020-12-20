#include "Setup.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Demo/DemoActor.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/UI/UI.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    void Setup::onStart()
    {
        m_pManager->getModule<UI>()->setActiveAll(false);
        auto world = m_pManager->getModule<World>();
        
        if (auto codeZero = world->find<Actor::Enemy::CodeZero::CodeZeroProxy>()) {
            world->create<Actor::Enemy::CodeZero::Demo::DemoActor>(codeZero->getPos());
            codeZero->setActive(false);
        }

        world->flush();
    }

    bool Setup::update([[maybe_unused]]double dt)
    {
        return false;
    }

}
