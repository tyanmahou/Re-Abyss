#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>

namespace abyss::UI::BossArrival
{
    class BossArrivalVM;

    class Main :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        Main(UIObj* pUi);

        void setup(Executer executer) override;

        void onStart() override;

        void onUpdate() override;

        Coro::Fiber<void> updateAsync();

        void onDraw()const override;
    private:
        UIObj* m_pUi;
        Coro::FiberHolder<> m_fiber;

        std::unique_ptr<BossArrivalVM> m_view;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<UI::BossArrival::Main>
    {
        using Base = MultiComponents<
            UI::IUpdate,
            UI::IDraw
        >;
    };
}
