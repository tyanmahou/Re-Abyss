#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class ComponentCache
    {
    protected:
        BehaviorCtrl* m_behavior;
    public:
        void onCache(ActorObj* pActor)
        {
            m_behavior = pActor->find<BehaviorCtrl>().get();
        }
    };
}