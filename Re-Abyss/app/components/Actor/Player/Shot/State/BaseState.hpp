#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Player/Shot/Collider.hpp>
#include <abyss/components/Actor/Player/Shot/PlayerShot.hpp>

namespace abyss::Actor::Player::Shot
{
    class BaseState : public IState
    {
    protected:
        PlayerShot* m_shot;
        Collider* m_collider;
    public:
        void setup()override;

        void start() override;

        void update() override;
    };
}