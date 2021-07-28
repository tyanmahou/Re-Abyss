#pragma once
#include <abyss/components/UI/Common/HierarchyCtrl.hpp>
#include <abyss/views/UI/Serif/CursorVM.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    class EraseUserConfirm : public IHierarchy
    {
    public:
        EraseUserConfirm(std::function<void()> callback);

        bool update() override;

        void draw() const override;

    private:
        bool m_yes = false;
        std::function<void()> m_callback;
        std::unique_ptr<UI::Serif::CursorVM> m_cursor;
    };
}