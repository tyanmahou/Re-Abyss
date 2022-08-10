#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/ComponentCache.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    class BaseState :
        public IState,
        public ComponentCache
    {
    public:
        void onCache() final;
    };
}
