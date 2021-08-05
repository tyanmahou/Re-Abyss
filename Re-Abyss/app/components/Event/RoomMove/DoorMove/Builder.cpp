#include "Builder.hpp"
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Event/base/IEvent.hpp>

#include <abyss/components/Event/RoomMove/RoomMoveCtrl.hpp>
#include <abyss/components/Event/RoomMove/DoorMove/RoomMoveCallback.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::RoomMove::DoorMove
{
    void Builder::Build(
        IEvent* pEvent,
        const RoomModel& nextRoom,
        const Actor::Gimmick::Door::DoorModel& door,
        const s3d::Vec2& playerPos,
        std::function<void()> fadeInCallback,
        double milliSec
    ) {
        assert(milliSec > 0);

        // 移動制御
        {
            auto manager = pEvent->getManager();
            auto camera = manager->getModule<Camera>();

            const auto& current = camera->getCurrentRoom();
            Vec2 playerFrom = door.fixedVisiterPos();
            Vec2 playerTo = door.getTargetPos();
            Vec2 from = current.cameraBorderAdjusted(playerFrom);
            Vec2 to = nextRoom.cameraBorderAdjusted(playerTo);

            auto callback = std::make_unique<RoomMoveCallback>(
                pEvent,
                std::make_pair(from, to),
                std::make_pair(playerFrom, playerTo),
                playerPos,
                fadeInCallback
                );

            pEvent
                ->attach<RoomMoveCtrl>(pEvent, std::move(callback), nextRoom, milliSec)
                ->setCheckInDesc(CheckInDesc{
                    .isErpLight = false
                });
        }
    
        // フェード
        {
            pEvent->attach<FadeIrisOut>(pEvent);
        }
    }

}