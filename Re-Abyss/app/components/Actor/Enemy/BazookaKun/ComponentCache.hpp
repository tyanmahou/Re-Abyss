#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/TargetCtrl.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        TargetCtrl* m_target;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_target = pActor->find<TargetCtrl>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}
