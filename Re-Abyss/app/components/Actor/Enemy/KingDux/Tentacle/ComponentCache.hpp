#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ShakeCtrl.hpp>
#include <abyss/components/Actor/Common/RotateCtrl.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/RetireCtrl.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        RotateCtrl* m_rotate;
        ShakeCtrl* m_shake;
        BehaviorCtrl* m_behavior;
        RetireCtrl* m_retireCtrl;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_rotate = pActor->find<RotateCtrl>().get();
            m_shake = pActor->find<ShakeCtrl>().get();
            m_behavior = pActor->find<BehaviorCtrl>().get();
            m_retireCtrl = pActor->find<RetireCtrl>().get();
        }
    };
}