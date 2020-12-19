#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>

#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Player/Shot/Collider.hpp>
#include <abyss/components/Actors/Player/Shot/PlayerShot.hpp>
#include <abyss/views/Actors/Player/Shot/ShotVM.hpp>

namespace abyss::Actor::Player::Shot
{
    class BaseState : public IState
    {
    protected:
        PlayerShot* m_shot;
        Collider* m_collider;
        ViewCtrl<ShotVM>* m_view;
    public:
        void setup()override;

        Task<> start() override;

        void update() override;

        void draw() const override;
    };
}