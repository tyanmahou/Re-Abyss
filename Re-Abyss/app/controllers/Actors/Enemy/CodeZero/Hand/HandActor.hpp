#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/models/Actors/base/OldStateModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Hand/HandModel.hpp>

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
        Ref<BodyModel> m_body;
        Ref<RotateModel> m_rotate;
        Ref<HandModel> m_hand;
        Kind m_kind;
        Ref<OldStateModel<HandActor>> m_state;
        std::shared_ptr<HandVM> m_view;
    public:
        HandActor(CodeZeroActor* parent, Kind kind);

        CShape getCollider() const;
        bool accept(const ActVisitor& visitor) override;

        HandVM* getBindedView()const;
        Kind getKind()const { return m_kind; }
        bool isLeftHand()const { return m_kind == Kind::Left; }
        bool isRightHand()const { return m_kind == Kind::Right; }

        void changeState(State state);
        bool tryAttack();
        bool tryPursuit();
        bool tryShotCharge();

        bool isShotCharge()const;
        bool isPursuit() const;
    };
}