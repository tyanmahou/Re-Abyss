#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/Main.hpp>
#include <abyss/views/Actor/Enemy/KingDux/BabyDux/Motion.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    class ComponentCache
    {
    protected:
        Main* m_main = nullptr;
        Body* m_body;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            if (auto main = pActor->find<Main>()) {
                m_main = main.get();
            }
            m_body = pActor->find<Body>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}
