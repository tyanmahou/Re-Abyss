#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ShakeCtrl.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/views/Actor/Enemy/KingDux/Motion.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        ShakeCtrl* m_shake;
        BehaviorCtrl* m_behavior;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_shake = pActor->find<ShakeCtrl>().get();
            m_behavior = pActor->find<BehaviorCtrl>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}