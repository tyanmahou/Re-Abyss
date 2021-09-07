#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
#include "ComponentCache.hpp"

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