#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/RotateCtrl.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        RotateCtrl* m_rotate;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_rotate = pActor->find<RotateCtrl>().get();
        }
    };
}