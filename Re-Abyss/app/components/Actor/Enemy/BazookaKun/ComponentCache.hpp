#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    class ComponentCache
    {
    protected:
        Body* m_body;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
        }
    };
}
