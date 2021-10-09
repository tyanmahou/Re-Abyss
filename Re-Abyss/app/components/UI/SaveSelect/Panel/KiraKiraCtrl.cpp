#include "KiraKiraCtrl.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/DrawManager/DrawOrder.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    KiraKiraCtrl::KiraKiraCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_algo(pUi->getModule<Effects>(), DrawLayer::UI)
    {}

    void KiraKiraCtrl::onStart()
    {

    }

    void KiraKiraCtrl::onPostUpdate()
    {
        if (!m_isActive) {
            return;
        }
        m_algo.update(m_pos, m_pUi->deltaTime(), [](Effect::EffectObj* pObj) {
            pObj->setOrder(DrawOrder::UI::Default - 1.0);
        });
    }
}