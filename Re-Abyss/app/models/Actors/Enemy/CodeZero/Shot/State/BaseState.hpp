#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/ScaleModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Shot/ShotVM.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class BaseState : public IState
    {
    protected:
        ParentCtrlModel* m_parent;
        BodyModel* m_body;
        ScaleModel* m_scale;
        ViewModel<ShotVM>* m_view;
    public:
        void setup() override;

        void lastUpdate() override;

        void draw()const override;
    };
}