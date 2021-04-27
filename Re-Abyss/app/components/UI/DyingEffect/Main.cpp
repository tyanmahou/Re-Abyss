#include "Main.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/views/UI/DyingEffect/DyingEffectVM.hpp>

namespace abyss::UI::DyingEffect
{
    Main::Main(UIObj* pUi, Actor::IActor* pActor):
        m_pUi(pUi),
        m_pActor(pActor),
        m_view(std::make_unique<DyingEffectVM>())
    {}

    void Main::onStart()
    {
        m_hpModel = m_pActor->find<Actor::HP>();
        m_hp = 0;
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());
    }

    void Main::onUpdate()
    {
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());
        m_hp = static_cast<double>(m_hpModel->getHp());
    }


    void Main::onDraw() const
    {
        m_view
            ->setHp(m_hp)
            .setMaxHp(m_maxHp)
            .setTime(m_pUi->getModule<GlobalTime>()->time())
            .draw();
    }

}
