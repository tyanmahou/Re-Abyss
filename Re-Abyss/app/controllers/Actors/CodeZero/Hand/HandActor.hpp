#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/CodeZero/CodeZeroHandModel.hpp>

namespace abyss::CodeZero
{
    class CodeZeroActor;
}
namespace abyss::CodeZero::Hand
{
    class HandVM;

    class HandActor :
        public IActor,
        public Attacker
    {
    public:
        enum State
        {
            Pursuit,
            AttackWait,
            Attack,
            ShotCharge,
        };
        enum Kind
        {
            Left,
            Right
        };
    private:
        CodeZeroActor* m_parent;
        BodyModel m_body;
        RotateModel m_rotate;
        CodeZeroHandModel m_hand;
        Kind m_kind;
        StateManager<HandActor> m_state;
        std::shared_ptr<HandVM> m_view;
    public:
        HandActor(CodeZeroActor* parent, Kind kind);

        void update(double dt)override;
        void draw()const;

        CShape getCollider() const override;
        bool accept(const ActVisitor& visitor) override;

        HandVM* getBindedView()const;
        Kind getKind()const { return m_kind; }
        bool isLeftHand()const { return m_kind == Kind::Left; }
        bool isRightHand()const { return m_kind == Kind::Right; }

        void changeState(State state);
        bool tryAttack();
        bool tryPursuit();
        bool tryShotCharge();

        bool isShotCharge()const
        {
            return m_state.getState() == State::ShotCharge;
        }
        bool isPursuit() const
        {
            return m_state.getState() == State::Pursuit;
        }
    };
}