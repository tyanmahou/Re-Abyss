#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::Title::BackGround
{
    class BgCtrl;

    class BackGroundVM;
    class AtlantisVM;

    class ViewCtrl final :
        public IComponent,
        public IDraw
    {
    public:
        ViewCtrl(UIObj* pUi);
        ~ViewCtrl();
        void setup(Executer executer) override;
        void onStart() override;
        void onDraw() const override;
    private:
        UIObj* m_pUi;
        Ref<BgCtrl> m_bgCtrl;

        std::unique_ptr<BackGroundVM> m_bgView;
        std::unique_ptr<AtlantisVM> m_atlantisView;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Title::BackGround::ViewCtrl>
    {
        using Base = MultiComponents<UI::IDraw>;
    };
}