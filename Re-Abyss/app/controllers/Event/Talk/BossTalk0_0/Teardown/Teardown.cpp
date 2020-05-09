#include "Teardown.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Actors/CodeZero/Demo/DemoActor.hpp>
namespace abyss::Event::Talk::BossTalk0_0
{
    void Teardown::init()
    {
        auto world = m_pManager->getModule<World>();
       
        if (auto demoCodeZero = world->find<CodeZero::Demo::DemoActor>()) {
            demoCodeZero->destroy();
        }
    }

    bool Teardown::update([[maybe_unused]]double dt)
    {
        return false;
    }

}
