#include <abyss/components/UI/BossHPBar/HPGaugeCtrl.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/components/Actor/Common/HP.hpp>

namespace abyss::UI::BossHPBar
{
    HPGaugeCtrl::HPGaugeCtrl(UIObj* pUi, Ref<Actor::HP> hp, Ref<Actor::DamageCtrl> damage):
        m_pUi(pUi),
        m_hpRef(hp),
        m_damageRef(damage)
    {}
    void HPGaugeCtrl::onStart()
    {
        m_hp = 0;
        m_maxHp = static_cast<double>(m_hpRef->getMaxHp());
    }
    void HPGaugeCtrl::onUpdate()
    {
        if (!m_hpRef) {
            m_hp = 0;
            return;
        }
        m_maxHp = static_cast<double>(m_hpRef->getMaxHp());

        auto hp = static_cast<double>(m_hpRef->getHp());

        auto dt = m_pUi->getModule<GlobalTime>()->deltaTime();
        {
            double add = m_maxHp * dt;
            if (m_hp - add >= hp) {
                m_hp -= add;
            } else if (m_hp + add <= hp) {
                m_hp += add;
            } else {
                m_hp = hp;
            }
        }
        if (m_damageRef) {

            if (!m_damageRef->isInvincibleTime()) {
                m_hpComboTarget = hp;
            }

            {
                double add = m_maxHp * dt;
                double sub = m_maxHp * dt * 0.2;
                if (m_hpComboBuffer - sub >= m_hpComboTarget) {
                    m_hpComboBuffer -= sub;
                } else if (m_hpComboBuffer + add <= m_hpComboTarget) {
                    m_hpComboBuffer += add;
                } else {
                    m_hpComboBuffer = m_hpComboTarget;
                }
            }
        }
    }
    bool HPGaugeCtrl::isFull() const
    {
        return m_hp >= m_maxHp;
    }
    bool HPGaugeCtrl::isValid() const
    {
        return static_cast<bool>(m_hpRef);
    }
}
