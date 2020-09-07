#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/views/Actors/Enemy/Schield/Shot/ShotVM.hpp>

namespace abyss::Actor::Enemy::Schield::Shot
{

    class BaseState : public IState
    {
    protected:
        ViewModel<ShotVM>* m_view;
    public:
        void setup()override;

        void start() override;

        void draw() const override;
    };
}