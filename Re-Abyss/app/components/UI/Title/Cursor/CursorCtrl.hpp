#pragma once
#include <memory>
#include <array>
#include <functional>
#include <Siv3D/Timer.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>

namespace abyss::UI::Title::Cursor
{
    class Shot;
    class CursorVM;

    class CursorCtrl final:
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        enum class Mode
        {
            GameStart,
            Exit,

            Min = GameStart,
            Max = Exit,
            Term
        };
        static constexpr size_t ModeTerm = static_cast<size_t>(Mode::Term);
    public:
        CursorCtrl(UIObj* pUi);
        ~CursorCtrl();

        void onStart() override;
        void onUpdate() override;

        void onDraw()const override;

        bool isDone() const
        {
            return m_isDone;
        }
    private:
        std::function<void()>& operator[](Mode mode)
        {
            return m_events[static_cast<size_t>(mode)];
        }
    private:
        UIObj* m_pUi;
        Mode m_mode = Mode::GameStart;

        std::array<std::function<void()>, ModeTerm> m_events;
        std::unique_ptr<CursorVM> m_view;

        s3d::Timer m_gameStartTimer;
        bool m_isSelected = false;
        std::unique_ptr<Shot> m_shot;

        bool m_isDone = false;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Title::Cursor::CursorCtrl>
    {
        using Base = MultiComponents<UI::IUpdate, UI::IDraw>;
    };
}
