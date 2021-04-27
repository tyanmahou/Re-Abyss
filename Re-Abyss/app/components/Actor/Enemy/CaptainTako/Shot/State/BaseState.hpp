#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>

#include <abyss/components/Actor/Commons/ViewCtrl.hpp>
#include <abyss/views/Actor/Enemy/CaptainTako/Shot/ShotVM.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{

    class BaseState : public IState
    {
        ViewCtrl<ShotVM>* m_view;
    public:
        void setup()override;

        Task<> start() override;

        void draw() const override;
    };
}