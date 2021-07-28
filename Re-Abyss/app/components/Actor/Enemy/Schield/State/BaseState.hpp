#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Common/ViewCtrl.hpp>
#include <abyss/components/Actor/Enemy/Schield/FaceCtrl.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
#include <abyss/views/Actor/Enemy/Schield/SchieldVM.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class BaseState : public IState
    {
    protected:
        FaceCtrl* m_face;
        Body* m_body;
        ViewCtrl<SchieldVM>* m_view;
    public:
        void setup()override;
    };
}
