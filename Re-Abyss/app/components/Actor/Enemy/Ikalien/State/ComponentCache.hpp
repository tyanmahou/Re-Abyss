#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/RotateCtrl.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/views/Actor/Enemy/Ikalien/Motion.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        RotateCtrl* m_rotate;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_rotate = pActor->find<RotateCtrl>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}