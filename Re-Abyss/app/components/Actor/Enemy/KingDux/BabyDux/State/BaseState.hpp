#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/ComponentCache.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    class BaseState :
        public IState,
        public ComponentCache
    {
    public:
        void onCache() final;
    };
}