#pragma once
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Player/ComponentCache.hpp>

namespace abyss::Actor::Player
{
    class BaseState : 
        public IState,
        public ComponentCache
    {
    protected:

        virtual void onLanding(){}

    public:
        void onCache()override;

        void start() override;

        void update() override;

        void lastUpdate() override;
    };
}