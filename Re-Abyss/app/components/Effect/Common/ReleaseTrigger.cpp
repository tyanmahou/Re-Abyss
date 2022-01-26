#include <abyss/components/Effect/Common/ReleaseTrigger.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
namespace abyss::Effect
{
    ReleaseTrigger::ReleaseTrigger(EffectObj* pObj):
        m_pObj(pObj)
    {}
    void ReleaseTrigger::onUpdate()
    {
        if (m_trigger && m_trigger()) {
            m_pObj->destroy();
        }
    }
}
