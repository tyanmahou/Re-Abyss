#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include "../ComponentCache.hpp"

namespace abyss::Actor::Enemy::CodeZero
{
    class BaseState :
        public IState,
        public ComponentCache
    {
    public:
        BaseState();
        void onCache()override;

        void update() override;
    };
}