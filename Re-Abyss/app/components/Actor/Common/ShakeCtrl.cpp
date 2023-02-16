#include <abyss/components/Actor/Common/ShakeCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
    ShakeCtrl::ShakeCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void ShakeCtrl::onUpdate()
    {
        double dt = m_pActor->deltaTime();
        m_shake.update(dt);
    }
    void ShakeCtrl::request(double maxOffset, double timeSec)
    {
        m_shake.request(maxOffset, timeSec);
    }
    bool ShakeCtrl::isShakeing() const
    {
        return m_shake.isShakeing();
    }
}
