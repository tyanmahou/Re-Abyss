#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
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
        ViewModel<SchieldVM>* m_view;
    public:
        void setup()override;
    };
}
