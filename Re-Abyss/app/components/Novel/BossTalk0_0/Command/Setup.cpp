#include "Setup.hpp"

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/Novel/Common/MessageBox.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/CodeZeroProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Demo/Builder.hpp>

namespace abyss::Novel::BossTalk0_0
{
    Setup::Setup(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void Setup::onStart()
    {
        auto world = m_pTalk->getModule<World>();
        
        if (auto codeZero = world->find<Actor::Enemy::CodeZero::CodeZeroProxy>()) {
            world->create<Actor::Enemy::CodeZero::Demo::Builder>(codeZero->getPos());
            codeZero->setActive(false);
        }

        world->flush();
    }

    Coro::Task<> Setup::onCommand()
    {
        co_return;
    }
}
