#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandMove.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Hand/Motion.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class ComponentCache
    {
    protected:
        HandMove* m_handMove;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            m_handMove = pActor->find<HandMove>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}