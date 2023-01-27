#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/UI/Splash/Logo/LogoTimer.hpp>
#include <abyss/utils/Ref/Ref.hpp>


namespace abyss::UI::Splash::Logo
{
    class LogoVM;

    class LogoCtrl :
        public IComponent,
        public IUpdate,
        public IDraw
    {

    public:
        LogoCtrl(UIObj* pUi);
        ~LogoCtrl();
        void onUpdate() override;

        void onDraw() const override;

        bool isEnd() const;
    private:
        UIObj* m_pUi;

        LogoTimer m_timer;
        std::unique_ptr <Logo::LogoVM> m_view;
        bool m_isForceEnd = false;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Splash::Logo::LogoCtrl>
    {
        using Base = MultiComponents<UI::IUpdate, UI::IDraw>;
    };
}