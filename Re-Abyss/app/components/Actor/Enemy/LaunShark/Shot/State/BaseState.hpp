#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/RotateCtrl.hpp>
#include <abyss/components/Common/ViewCtrl.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
#include <abyss/views/Actor/Enemy/LaunShark/Shot/ShotVM.hpp>

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