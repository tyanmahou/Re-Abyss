#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HeadCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/WingCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ComponentCache
    {
    public:
        void onCache(ActorObj* pActor)
        {
            m_behavior = pActor->find<BehaviorCtrl>().get();
            m_parts = pActor->find<PartsCtrl>().get();
            m_head = pActor->find<HeadCtrl>().get();
            m_damageCtrl = pActor->find<DamageCtrl>().get();
            m_wing = pActor->find<WingCtrl>().get();
        }
    protected:
        BehaviorCtrl* m_behavior;
        PartsCtrl* m_parts;
        HeadCtrl* m_head;
        WingCtrl* m_wing;
        DamageCtrl* m_damageCtrl;
    };
}
