#include "RoomMoveChecker.hpp"

#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Event/Events.hpp>

#include <abyss/modules/Actors/Player/PlayerManager.hpp>
#include <abyss/components/Events/RoomMove/BasicMove/Builder.hpp>

#include <abyss/components/Actors/Commons/CameraFixPos.hpp>

namespace abyss::Actor::Player
{
    RoomMoveChecker::RoomMoveChecker(IActor* pActor):
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
        auto* player = m_pActor->getModule<PlayerManager>();
        const s3d::Vec2& pos = player->getPos();
        auto camera = m_pActor->getModule<Camera>();
        if (camera->canNextRoom(pos)) {
            if (auto nextRoom = m_pActor->getModule<Stage>()->findRoom(pos)) {
                // 移動開始
                m_pActor->getModule<Events>()
                    ->create<Event::RoomMove::BasicMove::Builder>(*nextRoom);
            }
        }
    }
}
