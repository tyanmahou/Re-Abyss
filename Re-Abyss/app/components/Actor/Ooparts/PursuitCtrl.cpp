#include <abyss/components/Actor/Ooparts/PursuitCtrl.hpp>
#include <Siv3D.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::Ooparts
{
    PursuitCtrl::PursuitCtrl(ActorObj* pActor, const Ref<Body>& pParent):
        m_pActor(pActor),
        m_pParent(pParent),
        m_localPos(0, 0)
    {}

    void PursuitCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void PursuitCtrl::onPreDraw()
    {
        if (!m_pParent) {
            return;
        }
        if (m_isPursuit) {
            auto dt = m_pActor->deltaTime();
            double time = m_pActor->getTimeSec();

            auto localTarget = Vec2{ m_pParent->getForward() * -20 , -40 };
            localTarget += Vec2{
                15 * s3d::Sin(time * 2.0),
                10 * s3d::Sin(time * 4.0)
            };
            auto diff = localTarget - m_localPos;
            if (!diff.isZero()) {
                constexpr double speed = 60.0f;
                m_localPos += diff.normalized() * speed * dt;
            }
        }
        m_body->setForward(m_pParent->getForward());
        m_body->setPos(m_pParent->getPos() + m_localPos);
    }

}
