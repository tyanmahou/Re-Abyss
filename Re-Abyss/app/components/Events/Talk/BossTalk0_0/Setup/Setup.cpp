#include "Setup.hpp"

#include <abyss/modules/Event/Talk/TalkObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/UI/UI.hpp>

#include <abyss/components/Actors/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Demo/Builder.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    Setup::Setup(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void Setup::onStart()
    {
        m_pTalk->getModule<UI>()->setActiveAll(false);
        auto world = m_pTalk->getModule<World>();
        
        if (auto codeZero = world->find<Actor::Enemy::CodeZero::CodeZeroProxy>()) {
            world->create<Actor::Enemy::CodeZero::Demo::Builder>(codeZero->getPos());
            codeZero->setActive(false);
        }

        world->flush();
    }

    Coro::Task<> Setup::onTalk()
    {
        co_return;
    }
}
