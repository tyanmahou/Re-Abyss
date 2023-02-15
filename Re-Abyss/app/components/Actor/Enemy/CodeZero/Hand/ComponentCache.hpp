#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandMove.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Hand/Motion.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class ComponentCache
    {
    public:
        void onCache(ActorObj* pActor)
        {
            m_handMove = pActor->find<HandMove>().get();
            m_colCtrl = pActor->find<ColCtrl>().get();
            m_motion = pActor->find<MotionCtrl>().get();
            m_parent = pActor->find<ParentCtrl>().get();
        }
    protected:
        HandMove* m_handMove;
        ColCtrl* m_colCtrl;
        MotionCtrl* m_motion;
        ParentCtrl* m_parent;
    };
}
