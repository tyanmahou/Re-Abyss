#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/HandCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/KindCtrl.hpp>

#include <abyss/views/Actors/Enemy/CodeZero/Hand/HandVM.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class CodeZeroActor;
}
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class BaseState : public IState
    {
    protected:
        ParentCtrl* m_parent;
        BodyModel* m_body;
        RotateCtrl* m_rotate;
        HandCtrl* m_hand;
        KindCtrl* m_kind;
        ViewCtrl<HandVM>* m_view;
    public:
        void setup()override;
        void update(double dt) override;
        void draw() const override;
    };
}