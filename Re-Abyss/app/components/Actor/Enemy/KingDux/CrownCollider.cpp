#include "CrownCollider.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    void CrownCollider::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    CShape CrownCollider::getCollider() const
    {
        const auto& shapes = Param::Base::CrownColliders;
        Array<CShape> ret(shapes.size());
        for (const auto& tri : shapes) {
            ret.emplace_back(tri.movedBy(m_body->getPos()));
        }
        return ret;
    }
    CrownCollider::CrownCollider(ActorObj* pActor) :
        m_pActor(pActor)
    {}
}