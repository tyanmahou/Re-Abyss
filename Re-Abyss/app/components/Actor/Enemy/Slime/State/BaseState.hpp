#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/Slime/ComponentCache.hpp>

namespace abyss::Actor::Enemy::Slime
{

    class BaseState : 
        public IState,
        public ComponentCache
    {
    public:
        void onCache()override;

        void updateMove();
        void checkWallHit();
    };
}