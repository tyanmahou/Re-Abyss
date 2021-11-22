#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::Title::Logo
{
    class LogoCtrl;
    class LogoVM;

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
        Ref<LogoCtrl> m_logoCtrl;

        std::unique_ptr <LogoVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Title::Logo::ViewCtrl>
    {
        using Base = MultiComponents<UI::IDraw>;
    };
}