#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/State/BaseState.hpp>
#include <abyss/components/Adv/CodeZeroDemo/SignalCtrl.hpp>

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
        Coro::Fiber<> task() override;
        void update() override;
    private:
        Fiber<> onEvent(Ref<Adv::CodeZeroDemo::SignalCtrl> signalCtrl);
        Fiber<> commonDead();
    };
}
