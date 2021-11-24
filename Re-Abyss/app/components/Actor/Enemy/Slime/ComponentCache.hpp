#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Actor/Common/CliffChecker.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/views/Actor/Enemy/Slime/Motion.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        AudioSource* m_audio;
        MapCollider* m_mapCol;
        CliffChecker* m_cliffChecker;
        MotionCtrl* m_motion;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_audio = pActor->find<AudioSource>().get();
            m_mapCol = pActor->find<MapCollider>().get();
            m_cliffChecker = pActor->find<CliffChecker>().get();
            m_motion = pActor->find<MotionCtrl>().get();
        }
    };
}