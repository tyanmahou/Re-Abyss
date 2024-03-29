#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ComponentCache.hpp>

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