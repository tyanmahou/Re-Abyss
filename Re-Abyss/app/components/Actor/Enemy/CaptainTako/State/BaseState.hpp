#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/ViewCtrl.hpp>
#include <abyss/views/Actor/Enemy/CaptainTako/CpatainTakoVM.hpp>

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