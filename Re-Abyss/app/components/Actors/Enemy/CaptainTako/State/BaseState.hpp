#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/views/Actors/Enemy/CaptainTako/CpatainTakoVM.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class BaseState : public IState
    {
    protected:
        Body* m_body;
        ViewCtrl<CaptainTakoVM>* m_view;
    public:
        void setup()override;
    };
}