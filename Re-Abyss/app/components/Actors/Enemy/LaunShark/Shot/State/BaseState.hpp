#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
#include <abyss/views/Actors/Enemy/LaunShark/Shot/ShotVM.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{

    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        RotateModel* m_rotate;
        ViewCtrl<ShotVM>* m_view;
    public:
        void setup()override;
    };
}