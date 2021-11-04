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

namespace abyss::UI::Message
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

        bool isVisible() const
        {
            return m_isVisible;
        }
        void setVisible(bool isVisible)
        {
            m_isVisible = isVisible;
        }
    private:
        UIObj* m_pUi;

        Ref<Novel::Engine> m_engine;

        std::unique_ptr<MessageBoxVM> m_boxView;
        std::unique_ptr<CursorVM> m_cursorView;

        bool m_isVisible = false;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Message::Main>
    {
        using Base = MultiComponents<UI::IUpdate, UI::IDraw>;
    };
}