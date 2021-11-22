#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/Foot.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>

#include <abyss/components/Actor/Player/AttackCtrl.hpp>
#include <abyss/components/Actor/Player/StateChecker.hpp>

#include <abyss/views/Actor/Player/Motion.hpp>

namespace abyss::Actor::Player
{
    class ComponentCache
    {
    protected:
        Body* m_body;
        AudioSource* m_audio;
        Foot* m_foot;
        MapCollider* m_mapCol;
        DamageCtrl* m_damageCtrl;
        ColCtrl* m_colCtrl;
        MotionCtrl* m_motion;

        AttackCtrl* m_attackCtrl;
        StateChecker* m_stateChecker;
    public:
        void onCache(ActorObj* pActor)
        {
            m_body         = pActor->find<Body>().get();
            m_audio        = pActor->find<AudioSource>().get();
            m_foot         = pActor->find<Foot>().get();
            m_mapCol       = pActor->find<MapCollider>().get();
            m_damageCtrl   = pActor->find<DamageCtrl>().get();
            m_colCtrl      = pActor->find<ColCtrl>().get();
            m_motion       = pActor->find<MotionCtrl>().get();

            m_stateChecker = pActor->find<StateChecker>().get();
            m_attackCtrl   = pActor->find<AttackCtrl>().get();
        }
    };
}