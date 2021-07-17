#pragma once
#include <memory>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/Splash/Logo/LogoCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::Splash
{
    class Main final : 
        public IComponent,
        public IUpdate
    {
        
    public:
        Main(UIObj* pUi);

        void setup(Executer executer) override;

        void onStart() override;

        void onUpdate() override;
    private:
        UIObj* m_pUi;
        Ref <Logo::LogoCtrl> m_logo;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Splash::Main>
    {
        using Base = MultiComponents<UI::IUpdate>;
    };
}