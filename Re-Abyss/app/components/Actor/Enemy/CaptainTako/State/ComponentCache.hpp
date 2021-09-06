#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/AudioSource.hpp>
#include <abyss/components/Actor/Enemy/CaptainTako/ChargeCtrl.hpp>

#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/views/Actor/Enemy/CaptainTako/Motion.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        AudioSource* m_audio;
        MotionCtrl* m_motion;
        ChargeCtrl* m_charge;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body = pActor->find<Body>().get();
            m_audio = pActor->find<AudioSource>().get();
            m_motion = pActor->find<MotionCtrl>().get();
            m_charge = pActor->find<ChargeCtrl>().get();
        }
    };
}