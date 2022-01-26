#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/LaunShark/Shot/ComponentCache.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class BaseState :
        public IState,
        public ComponentCache
    {
    public:
        void onCache()override;
    };
}