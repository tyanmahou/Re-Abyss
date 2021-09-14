#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{

    class BaseState : public IState
    {
    public:
        void start() override;
    };
}