#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/MapCollider.hpp>
#include <abyss/components/Actor/Commons/TimeCounter.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/views/Actor/Enemy/LaunShark/Motion.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        MapCollider* m_mapCol;
        TimeCounter* m_timeCounter;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_mapCol = pActor->find<MapCollider>().get();
            m_timeCounter = pActor->find<TimeCounter>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}