#include <abyss/components/Actor/Player/RoomMoveChecker.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Event/Events.hpp>

#include <abyss/modules/Actor/Player/PlayerManager.hpp>
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
        auto* player = m_pActor->getModule<PlayerManager>();
        const s3d::Vec2& pos = player->getPos();
        auto roomManager = m_pActor->getModule<RoomManager>();
        if (roomManager->canNextRoom(pos)) {
            if (auto nextRoom = m_pActor->getModule<Stage>()->findRoom(pos)) {
                // 移動開始
                pEvent->create<Event::RoomMove::BasicMove::Builder>(*nextRoom);
            }
        }
    }
}
