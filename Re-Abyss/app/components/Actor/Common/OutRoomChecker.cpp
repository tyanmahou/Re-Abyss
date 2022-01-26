#include <abyss/components/Actor/Common/OutRoomChecker.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/utils/Collision/CollisionUtil.hpp>
#include <abyss/utils/Overloaded.hpp>

namespace abyss::Actor
{
    OutRoomChecker::OutRoomChecker(ActorObj* pActor) :
        m_pActor(pActor)
    {}

    void OutRoomChecker::setup(Executer executer)
    {
        executer.on<ILastUpdate>().addBefore<DeadChecker>();
    }

    void OutRoomChecker::onStart()
    {
        m_deadChecker = m_pActor->find<DeadChecker>();
        if (!m_colliderFunc) {
            if (auto col = m_pActor->find<Collider>(); !col->empty()) {
                auto mainCol = col->main();
                m_colliderFunc = [mainCol] {
                    return mainCol->getCollider();
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

        s3d::RectF roomRect = m_pActor->getModule<RoomManager>()->currentRoom().getRegion();
        m_isOutRoom = !ColisionUtil::Intersects(roomRect, m_colliderFunc());

        if (m_isOutRoom && m_isAutoDestroy && m_deadChecker) {
            m_deadChecker->requestDead();
        }
    }
}
