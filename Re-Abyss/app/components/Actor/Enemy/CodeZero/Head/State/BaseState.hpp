#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include "../ComponentCache.hpp"

namespace abyss::Actor::Enemy::CodeZero::Head
{
    class BaseState :
        public IState,
        public ComponentCache
    {
    public:
        void onCache()override;

        void update() override;
    };
}