#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/components/UI/SaveSelect/Main/UserSelector.hpp>
#include <abyss/views/UI/SaveSelect/SelectFrame/SelectFrameVM.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class SelectFrameCtrl : 
        public IComponent,
        public IDraw
    {
    public:
        SelectFrameCtrl(UIObj* pUi);

        void setup(Executer executer) override;
        void onStart() override;
        void onDraw() const override;
    private:
        UIObj* m_pUi;
        Ref<UserSelector> m_selector;
        std::unique_ptr<SelectFrame::SelectFrameVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::SaveSelect::Main::SelectFrameCtrl>
    {
        using Base = MultiComponents<
            UI::IDraw
        >;
    };
}
