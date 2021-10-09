#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/SaveSelect/Panel/Mode.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    class ModeCtrl : public IComponent
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
    private:
        UIObj* m_pUi;
        Mode m_mode = Mode::GameStart;
    };
}