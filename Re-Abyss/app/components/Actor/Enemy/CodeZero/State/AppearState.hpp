#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/State/BaseState.hpp>
#include <abyss/components/Adv/CodeZeroDemo/SignalCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class AppearState final :
        public BaseState,
        public std::enable_shared_from_this<AppearState>
    {
    public:
        void start() override;
        void end() override;
        Coro::Fiber<> task() override;
        void update() override;
    private:
        Fiber<> onDemo(Ref<Adv::CodeZeroDemo::SignalCtrl> signalCtrl);
        Fiber<> onAppear(Ref<Adv::CodeZeroDemo::SignalCtrl> signalCtrl);
        Fiber<> onPrepareBattle(Ref<Adv::CodeZeroDemo::SignalCtrl> signalCtrl);

        Ref<AppearState> getWeak()
        {
            return shared_from_this();
        }
    private:
        bool m_isSkip = false;
    };
}
