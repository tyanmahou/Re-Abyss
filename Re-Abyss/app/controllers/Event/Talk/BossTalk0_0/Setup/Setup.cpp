#include "Setup.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Demo/DemoActor.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/UI/UI.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    void Setup::init()
    {
        m_pManager->getModule<UI>()->setActiveAll(false);
        auto world = m_pManager->getModule<World>();
        
        if (auto codeZero = world->find<CodeZero::CodeZeroActor>()) {
            world->create<CodeZero::Demo::DemoActor>(codeZero->getPos());
            codeZero->setActiveAll(false);
        }

        world->flush();
    }

    bool Setup::update([[maybe_unused]]double dt)
    {
        return false;
    }

}
