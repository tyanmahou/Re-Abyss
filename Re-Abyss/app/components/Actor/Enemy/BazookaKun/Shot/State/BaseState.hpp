#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>

namespace abyss::Actor::Enemy::BazookaKun::Shot
{

    class BaseState : public IState
    {
    public:
        void onCache()override;

        void start() override;
    };
}
