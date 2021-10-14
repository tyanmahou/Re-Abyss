#include "Setup.hpp"

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Demo/Builder.hpp>

namespace abyss::Novel::BossTalk0_0
{
    Setup::Setup(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void Setup::onStart()
    {
        m_pTalk->getModule<UIs>()->setActiveAll(false);
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
