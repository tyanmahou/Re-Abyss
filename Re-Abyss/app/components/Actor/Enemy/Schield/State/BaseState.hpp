#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/Schield/ComponentCache.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class BaseState :
        public IState,
        public ComponentCache
    {
    public:
        void onCache()override;
    };
}
