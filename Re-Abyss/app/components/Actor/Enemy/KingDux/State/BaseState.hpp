#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/ComponentCache.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class BaseState :
        public IState,
        public ComponentCache
    {
    public:
        void onCache() final;
    };
}