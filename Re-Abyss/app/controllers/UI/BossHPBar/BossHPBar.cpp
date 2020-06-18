#include "BossHPBar.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/views/UI/BossHPBar/BossHPBarVM.hpp>

namespace abyss::ui
{
    BossHPBar::BossHPBar(IActor* actor):
        m_pActor(actor),
        m_view(std::make_unique<BossHPBarVM>())
    {}

    void BossHPBar::start()
    {
        m_hpModel = m_pActor->find<HPModel>();
        m_hp = 0;
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());
    }

    void BossHPBar::update(double dt)
    {
        if (!m_hpModel) {
            this->destroy();
            return;
        }
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());

        auto hp = static_cast<double>(m_hpModel->getHp());

        double add = m_maxHp * dt;
        if (m_hp - add >= hp) {
            m_hp -= add;
        } else if (m_hp + add <= hp) {
            m_hp += add;
        } else {
            m_hp = hp;
        }
    }


    void BossHPBar::draw() const
    {
        m_view
            ->setHp(m_hp)
            .setMaxHp(m_maxHp)
            .draw();
    }

    bool BossHPBar::isFull() const
    {
        return m_hp >= m_maxHp;
    }

}
