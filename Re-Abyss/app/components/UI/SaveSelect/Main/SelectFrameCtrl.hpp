#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/components/UI/SaveSelect/Main/Users.hpp>
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

        void onStart() override;
        void onDraw() const override;
    private:
        UIObj* m_pUi;
        Ref<Main::Users> m_users;
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
