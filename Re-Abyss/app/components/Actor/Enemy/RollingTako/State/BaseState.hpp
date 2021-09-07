#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/RollingTako/State/ComponentCache.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    class BaseState : 
        public IState,
        public ComponentCache
    {
    public:
        void onCache()override;

        void lastUpdate() override;
    };
}
