#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/RotateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
#include <abyss/views/Actors/Enemy/LaunShark/Shot/ShotVM.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{

    class BaseState : public IState
    {
    protected:
        Body* m_body;
        RotateCtrl* m_rotate;
        ViewCtrl<ShotVM>* m_view;
    public:
        void setup()override;
    };
}