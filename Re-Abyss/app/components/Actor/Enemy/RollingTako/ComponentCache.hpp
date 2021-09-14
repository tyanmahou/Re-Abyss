#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/views/Actor/Enemy/RollingTako/Motion.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        AudioSource* m_audio;
        MapCollider* m_mapCol;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_audio = pActor->find<AudioSource>().get();
            m_mapCol = pActor->find<MapCollider>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}