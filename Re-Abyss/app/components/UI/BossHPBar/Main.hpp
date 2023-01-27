#pragma once
#include <memory>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/components/UI/BossHPBar/HPGaugeCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::BossHPBar
{
    class BossHPBarVM;
}
namespace abyss::UI::BossHPBar
{
    class Main : 
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
        Ref<HPGaugeCtrl> m_hpGauge;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::BossHPBar::Main>
    {
        using Base = MultiComponents<UI::IUpdate>;
    };
}