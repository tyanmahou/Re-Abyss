#include "OutRoomChecker.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/models/Actors/Commons/DeadCheackerModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>

#include <abyss/utils/Overloaded.hpp>

namespace abyss::Actor
{
    OutRoomChecker::OutRoomChecker(IActor* pActor) :
        m_pActor(pActor)
    {}

    void OutRoomChecker::setup()
    {
        m_deadChecker = m_pActor->find<DeadCheckerModel>();
        if (!m_colliderFunc) {
            if (auto body = m_pActor->find<BodyModel>()) {
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
