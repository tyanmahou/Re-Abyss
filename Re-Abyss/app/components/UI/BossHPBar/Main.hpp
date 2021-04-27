#pragma once
#include <memory>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/components/UI/Common/ViewCtrl.hpp>
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
        public IUpdate,
        public IDraw
    {
        
    public:
        Main(UIObj* pUi);

        void setup(Executer executer) override;

        void onStart() override;

        void onUpdate() override;

        void onDraw() const override;
    private:
        UIObj* m_pUi;
        Ref<HPGaugeCtrl> m_hpGauge;
        Ref<ViewCtrl<BossHPBarVM>> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::BossHPBar::Main>
    {
        using Base = MultiComponents<UI::IUpdate, UI::IDraw>;
    };
}