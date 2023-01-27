#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/UI/Dialog/DialogResult.hpp>
#include <abyss/components/UI/GamePause/Result.hpp>
#include <abyss/views/UI/GamePause/BackGround/BackGroundVM.hpp>
#include <abyss/views/UI/Message/CursorVM.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss::UI::GamePause
{
    class Main :
        public UI::Dialog::DialogResult<Result>,
        public IUpdate,
        public IDraw
    {
    public:
        static void Build(UIObj* pUi);
    public:
        Main(UIObj* pUi);
        ~Main();

    public:
        void onStart() override;
        void onUpdate() override;
        void onDraw() const override;
    private:
        Coro::Fiber<> stateSelect();
    private:
        UIObj* m_pUi;
        Coro::FiberHolder<> m_state;

        bool m_isSelectContinue = true;
        std::unique_ptr<UI::GamePause::BackGround::BackGroundVM> m_bg;
        std::unique_ptr<UI::Message::CursorVM> m_cursor;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<UI::GamePause::Main>
    {
        using Base = MultiComponents<
            UI::IUpdate,
            UI::IDraw,
            UI::Dialog::DialogResult<UI::GamePause::Result>
        >;
    };
}
