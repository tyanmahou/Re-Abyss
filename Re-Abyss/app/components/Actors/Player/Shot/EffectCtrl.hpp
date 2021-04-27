#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IDraw.hpp>
#include <abyss/components/Actors/Player/Shot/PlayerShot.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>

namespace abyss::Actor::Player::Shot
{
    class EffectCtrl : 
        public IComponent,
        public IDraw
    {
    public:
        EffectCtrl(ActorObj* pActor);
        void setup([[maybe_unused]] Executer executer) override;
        void onStart() override;
        void onDraw()const;
    private:
        ActorObj* m_pActor;
        Ref<Body> m_body;
        Ref<PlayerShot> m_shot;

        IntervalTimer m_effectTimer;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::Shot::EffectCtrl>
    {
        using Base = Actor::IDraw;
    };
}