#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/State/BaseState.hpp>
#include <abyss/components/Novel/CodeZeroDemo/SignalCtrl.hpp>

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
        Task<> onEvent(Ref<Novel::CodeZeroDemo::SignalCtrl> signalCtrl);
        Task<> commonDead();
    };
}
