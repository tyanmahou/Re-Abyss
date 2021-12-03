#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/ComponentCache.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class BaseState :
        public IState,
        public ComponentCache
    {
    public:
        void onCache() final;
    };
}