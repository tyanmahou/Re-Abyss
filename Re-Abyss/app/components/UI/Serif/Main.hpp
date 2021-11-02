#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Novel
{
    class Engine;
}

namespace abyss::UI::Serif
{
    class MessageBoxVM;
    class CursorVM;

    class Main :
        public IComponent,
        public IUpdate,
        public IDraw
    {

    public:
        Main(
            UIObj* pUi,
            const Ref<Novel::Engine>& engine
        );

        void onStart() override;

        void onUpdate() override;

        void onDraw() const override;
    private:
        UIObj* m_pUi;

        Ref<Novel::Engine> m_engine;

        std::unique_ptr<MessageBoxVM> m_boxView;
        std::unique_ptr<CursorVM> m_cursorView;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Serif::Main>
    {
        using Base = MultiComponents<UI::IUpdate, UI::IDraw>;
    };
}