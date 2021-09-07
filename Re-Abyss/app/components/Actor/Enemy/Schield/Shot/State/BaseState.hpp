#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>

namespace abyss::Actor::Enemy::Schield::Shot
{

    class BaseState : public IState
    {
    public:
        void onCache()override;

        void start() override;
    };
}