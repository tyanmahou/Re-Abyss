#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Adv
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
            const Ref<Adv::Engine>& engine
        );
        ~Main();
        void onStart() override;

        void onUpdate() override;

        void onDraw() const override;

        bool isBusyAnim() const;
        bool isVisible() const;
        void setVisible(bool isVisible);
        void animToTail();
    private:
        UIObj* m_pUi;

        Ref<Adv::Engine> m_engine;

        std::unique_ptr<MessageBoxVM> m_boxView;
        std::unique_ptr<CursorVM> m_cursorView;

        bool m_isVisible = false;
        TimeLite::Timer m_showHideTimer;
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
