#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>

#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/models/Actors/Player/Shot/ColliderModel.hpp>
#include <abyss/models/Actors/Player/Shot/PlayerShotModel.hpp>
#include <abyss/views/Actors/Player/Shot/ShotVM.hpp>

namespace abyss::Actor::Player::Shot
{
    class BaseState : public IState
    {
    protected:
        PlayerShotModel* m_shot;
        ColliderModel* m_collider;
        ViewModel<ShotVM>* m_view;
    public:
        void setup()override;

        void start() override;

        void update(double dt) override;

        void draw() const override;
    };
}