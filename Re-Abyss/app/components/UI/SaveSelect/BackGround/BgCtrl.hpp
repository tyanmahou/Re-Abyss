#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/UI/SaveSelect/Main/ModeCtrl.hpp>
#include <abyss/views/UI/SaveSelect/BackGround/BackGroundVM.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::SaveSelect::BackGround
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
        Ref<Main::ModeCtrl> m_mode;
        std::unique_ptr<BackGroundVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::SaveSelect::BackGround::BgCtrl>
    {
        using Base = MultiComponents<UI::IDraw>;
    };
}