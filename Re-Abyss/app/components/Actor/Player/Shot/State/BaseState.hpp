#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Player/Shot/MainCollider.hpp>
#include <abyss/components/Actor/Player/Shot/PlayerShot.hpp>

namespace abyss::Actor::Player::Shot
{
    class BaseState : public IState
    {
    protected:
        PlayerShot* m_shot;
        MainCollider* m_collider;
    public:
        void onCache()override;

        void start() override;

        void update() override;
    };
}