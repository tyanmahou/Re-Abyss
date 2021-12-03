#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        BehaviorCtrl* m_behavior;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_behavior = pActor->find<BehaviorCtrl>().get();
        }
    };
}