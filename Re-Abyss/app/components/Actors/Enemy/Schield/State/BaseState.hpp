#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Enemy/Schield/FaceCtrl.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
#include <abyss/views/Actors/Enemy/Schield/SchieldVM.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class BaseState : public IState
    {
    protected:
        FaceCtrl* m_face;
        BodyModel* m_body;
        ViewCtrl<SchieldVM>* m_view;
    public:
        void setup()override;
    };
}
