#include "MainCollider.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    void MainCollider::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    CShape MainCollider::getCollider() const
    {
        const auto& shapes = Param::Base::MainColliders;
        Array<CShape> ret(shapes.size());
        for (const auto& tri : shapes) {
            ret.emplace_back(tri.movedBy(m_body->getPos()));
        }
        return ret;
    }
    MainCollider::MainCollider(ActorObj* pActor) :
        m_pActor(pActor)
    {}
}