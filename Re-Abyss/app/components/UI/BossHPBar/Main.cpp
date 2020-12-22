#include "Main.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/views/UI/BossHPBar/BossHPBarVM.hpp>

namespace abyss::ui::BossHPBar
{
    Main::Main(IUserInterface* pUi, Actor::IActor* pActor):
        m_pUi(pUi),
        m_pActor(pActor),
        m_view(std::make_unique<BossHPBarVM>())
    {}

    void Main::onStart()
    {
        m_hpModel = m_pActor->find<Actor::HP>();
        m_hp = 0;
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());
    }

    void Main::onUpdate()
    {
        if (!m_hpModel) {
            m_pUi->destroy();
            return;
        }
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());

        auto hp = static_cast<double>(m_hpModel->getHp());

        auto dt = m_pUi->deltaTime();
        double add = m_maxHp * dt;
        if (m_hp - add >= hp) {
            m_hp -= add;
        } else if (m_hp + add <= hp) {
            m_hp += add;
        } else {
            m_hp = hp;
        }
    }


    void Main::onDraw() const
    {
        m_view
            ->setHp(m_hp)
            .setMaxHp(m_maxHp)
            .draw();
    }

    bool Main::isFull() const
    {
        return m_hp >= m_maxHp;
    }

}
