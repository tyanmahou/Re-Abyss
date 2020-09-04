#include "PursuitModel.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

namespace abyss::Actor::Ooparts
{
    PursuitModel::PursuitModel(IActor* pActor, const Ref<BodyModel>& pParent):
        m_pActor(pActor),
        m_pParent(pParent),
        m_localPos(0, 0)
    {}

    void PursuitModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }

    void PursuitModel::onPreDraw(double dt)
    {
        if (!m_pParent) {
            return;
        }
        if (m_isPursuit) {
            double time = m_pActor->getDrawTimeSec();

            auto localTarget = Vec2{ m_pParent->getForward() * -20 , -40 };
            localTarget += Vec2{
                15 * s3d::Sin(time * 2.0),
                10 * s3d::Sin(time * 4.0)
            };
            auto diff = localTarget - m_localPos;
            constexpr double speed = 60.0f;
            m_localPos += diff.normalized() * speed * dt;
        }
        m_body->setForward(m_pParent->getForward());
        m_body->setPos(m_pParent->getPos() + m_localPos);
    }

}
