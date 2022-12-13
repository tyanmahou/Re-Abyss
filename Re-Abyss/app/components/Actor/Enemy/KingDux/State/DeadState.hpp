#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>
#include <abyss/components/Novel/RoomGarder/SignalCtrl.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class DeadState final :
        public BaseState
    {
        enum class Phase
        {
            Wait,
            Explosion,
        };
    public:
        static void Change(ActorObj* pActor);
    public:
        void start() override;
        void end() override;
        Coro::Fiber<> task() override;
        void update() override;
    private:
        Fiber<> onDemo(Ref<Novel::RoomGarder::SignalCtrl> signalCtrl);
        Fiber<> commonDead();
    private:
        Phase m_phase = Phase::Wait;
        TimeLite::Timer m_timer{};
    };
}
