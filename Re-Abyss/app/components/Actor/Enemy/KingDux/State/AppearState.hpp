#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>
#include <abyss/components/Novel/RoomGarder/SignalCtrl.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class AppearState final :
        public BaseState
    {
    public:
        void start() override;
        void end() override;
        Coro::Fiber<> task() override;
        void update() override;
    private:
        Coro::Fiber<> onDemo(Ref<Novel::RoomGarder::SignalCtrl> signalCtrl);
    };
}
