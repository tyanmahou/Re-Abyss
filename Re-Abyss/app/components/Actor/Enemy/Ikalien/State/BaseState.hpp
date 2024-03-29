#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/Ikalien/ComponentCache.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    class BaseState : 
        public IState,
        public ComponentCache
    {
    public:
        void onCache()override;
    };
}
