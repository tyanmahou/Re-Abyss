#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ComponentCache
    {
    protected:
        BehaviorCtrl* m_behavior;
        PartsCtrl* m_parts;
    public:
        void onCache(ActorObj* pActor)
        {
            m_behavior = pActor->find<BehaviorCtrl>().get();
            m_parts = pActor->find<PartsCtrl>().get();
        }
    };
}