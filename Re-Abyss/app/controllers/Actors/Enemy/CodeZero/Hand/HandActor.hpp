#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>

namespace abyss::CodeZero
{
    class CodeZeroActor;
}
namespace abyss::CodeZero::Hand
{
    class HandModel;

    class HandActor :
        public IActor,
        public Attacker
    {
    public:
        enum class Kind
        {
            Left,
            Right
        };
    private:
        Ref<BodyModel> m_body;
        Ref<RotateModel> m_rotate;
        Ref<HandModel> m_hand;
        Ref<StateModel> m_state;
    public:
        HandActor(CodeZeroActor* parent, Kind kind);

        CShape getCollider() const;
        bool accept(const ActVisitor& visitor) override;

        bool tryAttack();
        bool tryPursuit();
        bool tryShotCharge();

        bool isShotCharge()const;
        bool isPursuit() const;
    };
}