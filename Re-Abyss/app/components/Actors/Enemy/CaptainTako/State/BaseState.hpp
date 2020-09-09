#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/views/Actors/Enemy/CaptainTako/CpatainTakoVM.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        ViewCtrl<CaptainTakoVM>* m_view;
    public:
        void setup()override;
    };
}