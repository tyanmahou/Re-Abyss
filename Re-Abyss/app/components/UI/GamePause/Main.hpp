#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/components/UI/Dialog/DialogResult.hpp>
#include <abyss/components/UI/GamePause/Result.hpp>
#include <abyss/utils/Coro/Task/TaskHolder.hpp>

#include <abyss/views/Shader/Dither/DitherShader.hpp>

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
        Coro::Task<> stateSelect();
    private:
        UIObj* m_pUi;
        Coro::TaskHolder<> m_state;

        DitherShader m_dither;
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
