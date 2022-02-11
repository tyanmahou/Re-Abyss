#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/Main.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    class ComponentCache
    {
    protected:
        Main* m_main;
        Body* m_body;
    public:
        void onCache(ActorObj* pActor)
        {
            m_main = pActor->find<Main>().get();
            m_body = pActor->find<Body>().get();
        }
    };
}