#include "Teardown.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Demo/DemoActor.hpp>
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
