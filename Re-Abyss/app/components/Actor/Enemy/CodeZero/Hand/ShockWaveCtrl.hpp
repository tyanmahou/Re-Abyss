#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/Common/IStateCallback.hpp>
#include <abyss/utils/TimeLite/IntervalTimer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandMove;

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
        Ref<HandMove> m_handMove;
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