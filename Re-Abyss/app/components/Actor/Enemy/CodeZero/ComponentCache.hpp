#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Common/HP.hpp>

namespace abyss::Actor::Enemy::CodeZero
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