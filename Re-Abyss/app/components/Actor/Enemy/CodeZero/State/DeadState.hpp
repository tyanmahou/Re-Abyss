#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/State/BaseState.hpp>
#include <abyss/components/Novel/BossTalk0_1/SignalCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class DeadState final :
        public BaseState
    {
    public:
        static void Change(ActorObj* pActor);
    public:
        void start() override;
        void end() override;
        Coro::Task<> task() override;
        void update() override;
    private:
        Task<> onEvent(Ref<Novel::BossTalk0_1::SignalCtrl> signalCtrl);
        Task<> commonDead();
    };
}