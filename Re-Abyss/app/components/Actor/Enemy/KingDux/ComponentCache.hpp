#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ShakeCtrl.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Common/VModelUpdater.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/EyeCtrl.hpp>
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
        VModelUpdater* m_modelUpdater;
        EyeCtrl* m_eyeCtrl;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_shake = pActor->find<ShakeCtrl>().get();
            m_behavior = pActor->find<BehaviorCtrl>().get();
            m_motion = pActor->find<MotionCtrl>().get();
            m_modelUpdater = pActor->find<VModelUpdater>().get();
            m_eyeCtrl = pActor->find<EyeCtrl>().get();
        }
    };
}