#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ComponentCache
    {
    protected:
        HP* m_hp;
        BehaviorCtrl* m_behavior;
        PartsCtrl* m_parts;
    public:
        void onCache(ActorObj* pActor)
        {
            m_hp = pActor->find<HP>().get();
            m_behavior = pActor->find<BehaviorCtrl>().get();
            m_parts = pActor->find<PartsCtrl>().get();
        }
    };
}