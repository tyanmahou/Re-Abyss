#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/components/UI/SaveSelect/Main/Mode.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class ModeCtrl :
        public IComponent,
        public IDraw
    {
    public:
        ModeCtrl(UIObj* pUi);

        void set(Mode mode)
        {
            m_mode = mode;
        }
        Mode get() const
        {
            return m_mode;
        }
        bool is(Mode mode) const
        {
            return m_mode == mode;
        }

        void onDraw() const override;
    private:
        UIObj* m_pUi;
        Mode m_mode = Mode::GameStart;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::SaveSelect::Main::ModeCtrl>
    {
        using Base = MultiComponents<
            UI::IDraw
        >;
    };
}
