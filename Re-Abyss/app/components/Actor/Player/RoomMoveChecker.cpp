#include <abyss/components/Actor/Player/RoomMoveChecker.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Event/Events.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Event/RoomMove/BasicMove/Builder.hpp>

#include <abyss/components/Actor/Common/CameraFixPos.hpp>

namespace abyss::Actor::Player
{
    RoomMoveChecker::RoomMoveChecker(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void RoomMoveChecker::setup(Executer executer)
    {
        // カメラでフィックスしてからやる
        executer.on<ILastUpdate>().addAfter<CameraFixPos>();
    }
    void RoomMoveChecker::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    void RoomMoveChecker::onLastUpdate()
    {
        if (m_pActor->isDestroyed()) {
            // 死んでたらやらない
            return;
        }
        auto* pEvent = m_pActor->getModule<Events>();
        if (!pEvent->isEmpty()) {
            // 他のイベント中
            return;
        }
        const s3d::Vec2& pos = m_body->getCenterPos();
        auto roomManager = m_pActor->getModule<RoomManager>();
        if (roomManager->canNextRoom(pos)) {
            if (auto nextRoom = m_pActor->getModule<Stage>()->findRoom(pos)) {
                // 移動開始
                pEvent->create<Event::RoomMove::BasicMove::Builder>(*nextRoom);
            }
        }
    }
}
