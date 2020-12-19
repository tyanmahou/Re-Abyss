#include "RoomMoveChecker.hpp"

#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/Stage/Stage.hpp>

#include <abyss/controllers/Event/RoomMove/BasicMove/BasicMove.hpp>

#include <abyss/components/Actors/Commons/CameraFixPos.hpp>

namespace abyss::Actor::Player
{
    RoomMoveChecker::RoomMoveChecker(PlayerActor* pActor):
        m_pActor(pActor)
    {}
    void RoomMoveChecker::setup(Depends depends)
    {
        // カメラでフィックスしてからやる
        depends.on<ILastUpdate>().addAfter<CameraFixPos>();
    }
    void RoomMoveChecker::onLastUpdate()
    {
        if (m_pActor->isDestroyed()) {
            // 死んでたらやらない
            return;
        }
        auto pos = m_pActor->getPos();
        auto camera = m_pActor->getModule<Camera>();
        if (camera->canNextRoom(pos)) {
            if (auto nextRoom = m_pActor->getModule<Stage>()->findRoom(pos)) {
                // 移動開始
                Event::RoomMove::BasicMove::Start(*m_pActor, *nextRoom);
            }
        }
    }
}
