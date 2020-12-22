#pragma once
#include <memory>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::ui::BossHPBar
{
    class BossHPBarVM;
}
namespace abyss::ui::BossHPBar
{
    /// <summary>
    /// HPゲージ制御
    /// </summary>
    class HPGaugeCtrl :
        public IComponent,
        public IUpdate
    {
    public:
        HPGaugeCtrl(Actor::IActor* pActor);

        void onStart() override;

        void onUpdate() override;

        bool isFull() const;

        bool isValid() const;

        double getHp() const
        {
            return m_hp;
        }
        double getMaxHp() const
        {
            return m_maxHp;
        }
    private:
        Actor::IActor* m_pActor;
        Ref<Actor::HP> m_hpModel;

        double m_hp = 0;
        double m_maxHp = 1;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<ui::BossHPBar::HPGaugeCtrl>
    {
        using Base = MultiComponents<ui::IUpdate>;
    };
}