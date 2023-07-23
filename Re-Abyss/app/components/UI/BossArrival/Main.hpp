#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss::UI::BossArrival
{
    class Main :
        public IComponent,
        public IUpdate
    {
    public:
        Main(UIObj* pUi);

        void setup(Executer executer) override;

        void onStart() override;

        void onUpdate() override;

        Coro::Fiber<void> updateAsync();
    private:
        UIObj* m_pUi;
        Coro::FiberHolder<> m_fiber;
    };
}
