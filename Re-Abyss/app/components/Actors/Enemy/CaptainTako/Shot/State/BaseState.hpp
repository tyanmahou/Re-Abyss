#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>

#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/views/Actors/Enemy/CaptainTako/Shot/ShotVM.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{

    class BaseState : public IState
    {
        ViewCtrl<ShotVM>* m_view;
    public:
        void setup()override;

        void start() override;

        void draw() const override;
    };
}