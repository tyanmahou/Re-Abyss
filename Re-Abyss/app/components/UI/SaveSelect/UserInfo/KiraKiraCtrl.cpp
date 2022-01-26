#include <abyss/components/UI/SaveSelect/UserInfo/KiraKiraCtrl.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/DrawManager/DrawOrder.hpp>
#include <abyss/components/Effect/Common/ReleaseTrigger.hpp>

namespace abyss::UI::SaveSelect::UserInfo
{
    KiraKiraCtrl::KiraKiraCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_algo(pUi->getModule<Effects>(), DrawLayer::UI)
    {}

    void KiraKiraCtrl::onStart()
    {

    }

    void KiraKiraCtrl::onUpdate()
    {
        if (m_releaseOneShot) {
            m_releaseOneShot = false;
        }
    }

    void KiraKiraCtrl::onPostUpdate()
    {
        if (!m_isActive) {
            return;
        }
        m_algo.update(m_pos, m_pUi->deltaTime(), [&](Effect::EffectObj* pObj) {
            pObj->setOrder(DrawOrder::UI::Default - 1.0);
            auto thisPtr = m_pUi->find<KiraKiraCtrl>();
            pObj->attach<Effect::ReleaseTrigger>(pObj)->setTrigger([thisPtr] {
                return thisPtr && (!thisPtr->m_isActive || thisPtr->m_releaseOneShot);
            });
        });
    }
}