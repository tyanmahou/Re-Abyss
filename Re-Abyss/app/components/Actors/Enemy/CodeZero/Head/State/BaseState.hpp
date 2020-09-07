#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Head/HeadModel.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Head/HeadVM.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
    class BaseState : public IState
    {
    protected:
        ParentCtrlModel* m_parent;
        HeadModel* m_head;

        ViewModel<HeadVM>* m_view;
    public:
        void setup()override;

        void update(double dt) override;

        void draw()const override;
    };
}