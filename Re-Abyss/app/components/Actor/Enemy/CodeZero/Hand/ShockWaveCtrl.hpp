#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/base/IStateCallback.hpp>
#include <abyss/utils/TimeLite/IntervalTimer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class ShockWaveCtrl final:
        public IComponent,
        public IPostCollision,
        public IStateCallback
    {
    public:
        ShockWaveCtrl(ActorObj* pActor);

        void onStart() override;
        void onPostCollision() override;

        void onStateStart() override;

        void setActive(bool isActive)
        {
            m_isActive = isActive;
        }
    private:
        ActorObj* m_pActor;
        TimeLite::IntervalTimer m_counter;
        bool m_isActive = false;

        Ref<Body> m_body;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::Hand::ShockWaveCtrl>
    {
        using Base = MultiComponents<
            Actor::IPostCollision,
            Actor::IStateCallback
        >;
    };
}