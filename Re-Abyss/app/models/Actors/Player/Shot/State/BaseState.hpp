#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/models/Actors/Player/Shot/PlayerShotModel.hpp>
#include <abyss/views/Actors/Player/Shot/ShotVM.hpp>

namespace abyss::Player::Shot
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        PlayerShotModel* m_shot;
        ViewModel<ShotVM>* m_view;
    public:
        void setup()override;

        void start() override;

        void update(double dt) override;

        void draw() const override;
    };
}