#pragma once
#include <memory>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::BossHPBar
{
    class BossHPBarVM;
}
namespace abyss::UI::BossHPBar
{
    /// <summary>
    /// HPゲージ制御
    /// </summary>
    class HPGaugeCtrl :
        public IComponent,
        public IUpdate
    {
    public:
        HPGaugeCtrl(UIObj* pUi, Ref<Actor::HP> hp, Ref<Actor::DamageCtrl> damage = nullptr);

        void onStart() override;

        void onUpdate() override;

        bool isFull() const;

        bool isValid() const;

        double getHp() const
        {
            return m_hp;
        }
        double getHpComboBuffer() const
        {
            return m_hpComboBuffer;
        }
        double getMaxHp() const
        {
            return m_maxHp;
        }
    private:
        UIObj* m_pUi;
        Ref<Actor::HP> m_hpRef;
        Ref<Actor::DamageCtrl> m_damageRef;

        double m_hp = 0;
        double m_hpComboBuffer = 0;
        double m_hpComboTarget = 0;
        double m_maxHp = 1;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::BossHPBar::HPGaugeCtrl>
    {
        using Base = MultiComponents<UI::IUpdate>;
    };
}
