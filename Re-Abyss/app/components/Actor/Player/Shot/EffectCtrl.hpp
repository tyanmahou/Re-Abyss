#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/Common/DrawBase.hpp>
#include <abyss/components/Actor/Player/Shot/PlayerShot.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimeLite/IntervalTimer.hpp>

namespace abyss::Actor::Player::Shot
{
    class EffectCtrl : 
        public IComponent,
        public IPreDraw,
        public DrawBase
    {
    public:
        EffectCtrl(ActorObj* pActor);
        void setup([[maybe_unused]] Executer executer) override;
        void onStart() override;
        void onPreDraw() override;
        void onDraw()const;
    private:
        ActorObj* m_pActor;
        Ref<Body> m_body;
        Ref<PlayerShot> m_shot;

        TimeLite::IntervalTimer m_effectTimer{ 0.033 };
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::Shot::EffectCtrl>
    {
        using Base = MultiComponents<
            Actor::IPreDraw,
            Actor::DrawBase
        >;
    };
}