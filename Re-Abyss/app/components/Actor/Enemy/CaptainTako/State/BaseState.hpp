#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/CaptainTako/ComponentCache.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class BaseState : 
        public IState,
        public ComponentCache
    {
    public:
        void onCache()override;
    };
}