#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/ScaleCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Shot/ShotVM.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class BaseState : public IState
    {
    protected:
        ParentCtrl* m_parent;
        BodyModel* m_body;
        ScaleCtrl* m_scale;
        ViewCtrl<ShotVM>* m_view;
    public:
        void setup() override;

        void lastUpdate() override;

        void draw()const override;
    };
}