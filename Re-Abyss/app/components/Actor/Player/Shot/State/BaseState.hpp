#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>

#include <abyss/components/Common/ViewCtrl.hpp>
#include <abyss/components/Actor/Player/Shot/Collider.hpp>
#include <abyss/components/Actor/Player/Shot/PlayerShot.hpp>
#include <abyss/views/Actor/Player/Shot/ShotVM.hpp>

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

        void start() override;

        void update() override;

        void draw() const override;
    };
}