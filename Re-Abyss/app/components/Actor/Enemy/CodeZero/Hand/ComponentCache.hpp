#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/KindCtrl.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Hand/Motion.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class ComponentCache
    {
    protected:
        ParentCtrl* m_parent;
        Body* m_body;
        RotateCtrl* m_rotate;
        HandCtrl* m_hand;
        KindCtrl* m_kind;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            m_parent = pActor->find<ParentCtrl>().get();
            m_body = pActor->find<Body>().get();
            m_rotate = pActor->find<RotateCtrl>().get();
            m_hand = pActor->find<HandCtrl>().get();
            m_kind = pActor->find<KindCtrl>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}