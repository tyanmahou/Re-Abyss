#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss::UI::Title
{
    class MainStream :
        public IComponent,
        public IUpdate
    {
    public:
        MainStream(UIObj* pUi);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        void onUpdate() override;
        Coro::Fiber<> onExecute();
    private:
        UIObj* m_pUi;
        Coro::FiberHolder<> m_fiber;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Title::MainStream>
    {
        using Base = MultiComponents<
            UI::IUpdate
        >;
    };
}
