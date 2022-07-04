#include <abyss/components/Actor/Enemy/KingDux/BabyDux/ForwardCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    ForwardCtrl::ForwardCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {
    }

    void ForwardCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    void ForwardCtrl::onLastUpdate()
    {
        const auto& pos = m_body->getPos();
        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);
        auto diff = playerPos - pos;

        if (m_body->isForward(Forward::Left) && diff.x > 100) {
            m_body->setForward(Forward::Right);
        } else if (m_body->isForward(Forward::Right) && diff.x < -100) {
            m_body->setForward(Forward::Left);
        }
    }
}
