#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/views/Actors/Enemy/Schield/Shot/ShotVM.hpp>

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