#include <abyss/components/Actor/Enemy/CodeZero/HeadCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    HeadCtrl::HeadCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
    s3d::Vec2 HeadCtrl::getPos() const
    {
        return m_body->getPos() + Param::Head::Offset;
    }

    const Look& HeadCtrl::getLook() const
    {
        return m_look;
    }

    s3d::Vec2 HeadCtrl::getCenterPos() const
    {
        return this->getPos() + s3d::Vec2{ 0, 10 };
    }
    void HeadCtrl::setActive(bool isActive)
    {
        m_isActive = isActive;
    }
    void HeadCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_parts = m_pActor->find<PartsCtrl>();
    }

    void HeadCtrl::onLastUpdate()
    {
        if (!m_isActive) {
            return;
        }
        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);
        auto pos = this->getCenterPos();

        Vec2 look{0 , 0};
        if (!m_parts->isShotCharge()) {
            if (playerPos.x > pos.x + 100) {
                look += Vec2{ 1, 0 };
            } else if (playerPos.x < pos.x - 100) {
                look -= Vec2{ 1, 0 };
            }

            if (playerPos.y > pos.y + 200) {
                look += Vec2{ 0, 1 };
            } else if (playerPos.y < pos.y - 100) {
                look -= Vec2{ 0, 1 };
            }
        }

        m_look = Look(look);
    }
    void HeadCtrl::onStateStart()
    {
        this->setActive(true);
    }
}

