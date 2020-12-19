#include "OutRoomChecker.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>
#include <abyss/utils/Overloaded.hpp>

namespace abyss::Actor
{
    OutRoomChecker::OutRoomChecker(IActor* pActor) :
        m_pActor(pActor)
    {}

    void OutRoomChecker::setup(Depends depends)
    {
        depends.on<ILastUpdate>().addBefore<DeadChecker>();
    }

    void OutRoomChecker::onStart()
    {
        m_deadChecker = m_pActor->find<DeadChecker>();
        if (!m_colliderFunc) {
            if (auto col = m_pActor->find<ICollider>()) {
                m_colliderFunc = [col] {
                    return col->getCollider();
                };
            } else if (auto body = m_pActor->find<Body>()) {
                m_colliderFunc = [body] {
                    return body->region();
                };
            }
        }
    }

    void OutRoomChecker::onLastUpdate()
    {
        if (!m_colliderFunc) {
            m_isOutRoom = false;
            return;
        }

        m_isOutRoom = false;

        auto room = m_pActor->getModule<Camera>()->getCurrentRoom().getRegion();
        m_isOutRoom = !ColisionUtil::Intersects(room, m_colliderFunc());

        if (m_isOutRoom && m_isAutoDestroy && m_deadChecker) {
            m_deadChecker->requestDead();
        }
    }
}
