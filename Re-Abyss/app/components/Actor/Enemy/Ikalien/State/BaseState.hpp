#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/Ikalien/State/ComponentCache.hpp>

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
