#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/HandModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/KindModel.hpp>

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
        ParentCtrlModel* m_parent;
        BodyModel* m_body;
        RotateModel* m_rotate;
        HandModel* m_hand;
        KindModel* m_kind;
        ViewModel<HandVM>* m_view;
    public:
        void setup()override;
        void update(double dt) override;
        void draw() const override;
    };
}