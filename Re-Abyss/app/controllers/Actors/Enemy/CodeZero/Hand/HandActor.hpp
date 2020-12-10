#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class CodeZeroActor;
}
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandCtrl;

    class HandActor :
        public IActor
    {
    public:
        enum class Kind
        {
            Left,
            Right
        };
    private:
        Ref<Actor::Body> m_body;
        Ref<RotateCtrl> m_rotate;
        Ref<HandCtrl> m_hand;
        Ref<StateCtrl> m_state;
    public:
        HandActor(IActor* parent, Kind kind);

        CShape getCollider() const;
        bool accept(const ActVisitor& visitor) override;

        bool tryAttack();
        bool tryPursuit();
        bool tryShotCharge();

        bool isShotCharge()const;
        bool isPursuit() const;
    };
}