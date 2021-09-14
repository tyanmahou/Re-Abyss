#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/components/Actor/Enemy/Schield/FaceCtrl.hpp>
#include <abyss/views/Actor/Enemy/Schield/Motion.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        FaceCtrl* m_face;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_face = pActor->find<FaceCtrl>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}