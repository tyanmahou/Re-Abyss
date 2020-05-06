#include "Setup.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/controllers/Actors/CodeZero/Demo/DemoActor.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    void Setup::init()
    {
        auto world = m_pManager->getModule<World>();
        auto codeZero = world->find<CodeZero::CodeZeroActor>();
        if (auto actor = codeZero.lock(); !codeZero.expired()) {
            world->create<CodeZero::Demo::DemoActor>(actor->getPos() + s3d::Vec2{ 0, 400 });
        }

        world->init();
    }

    bool Setup::update([[maybe_unused]]double dt)
    {
        return false;
    }

}
