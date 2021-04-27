#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/ViewCtrl.hpp>
#include <abyss/views/Actor/Enemy/Schield/Shot/ShotVM.hpp>

namespace abyss::Actor::Enemy::Schield::Shot
{

    class BaseState : public IState
    {
    protected:
        ViewCtrl<ShotVM>* m_view;
    public:
        void setup()override;

        Task<> start() override;

        void draw() const override;
    };
}