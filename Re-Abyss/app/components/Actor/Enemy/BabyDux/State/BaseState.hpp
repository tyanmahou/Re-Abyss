#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/BabyDux/ComponentCache.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
    class BaseState :
        public IState,
        public ComponentCache
    {
    public:
        void onCache() final;
    };
}
