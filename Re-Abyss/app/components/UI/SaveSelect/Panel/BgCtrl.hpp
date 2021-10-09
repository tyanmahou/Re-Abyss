#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/components/UI/SaveSelect/Panel/ModeCtrl.hpp>
#include <abyss/views/UI/SaveSelect/BackGround/BackGroundVM.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    class BgCtrl : 
        public IComponent,
        public IDraw
    {
    public:
        BgCtrl(UIObj* pUi);

        void onStart();
        void onDraw() const override;
    private:
        UIObj* m_pUi;
        Ref<ModeCtrl> m_mode;
        std::unique_ptr<BackGround::BackGroundVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::SaveSelect::Panel::BgCtrl>
    {
        using Base = MultiComponents<UI::IDraw>;
    };
}