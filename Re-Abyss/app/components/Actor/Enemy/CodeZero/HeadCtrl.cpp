#include <abyss/components/Actor/Enemy/CodeZero/HeadCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    HeadCtrl::HeadCtrl(ActorObj* pActor):
        m_forward(Forward::None),
        m_pActor(pActor)
    {}
    void HeadCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_parts = m_pActor->find<PartsCtrl>();
    }

    s3d::Vec2 HeadCtrl::getPos() const
    {
        return m_body->getPos() + Param::Head::Offset;
    }

    Forward HeadCtrl::getForward() const
    {
        return m_forward;
    }

    s3d::Vec2 HeadCtrl::getCenterPos() const
    {
        return this->getPos() + s3d::Vec2{ 0, 10 };
    }

    void HeadCtrl::onLastUpdate()
    {
        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);
        auto pos = this->getCenterPos();

        if (m_parts->isShotCharge()) {
            m_forward = Forward::None;
        } else if (playerPos.x > pos.x + 200) {
            m_forward = Forward::Right;
        } else if (playerPos.x < pos.x - 200) {
            m_forward = Forward::Left;
        } else {
            m_forward = Forward::None;
        }
    }

}

