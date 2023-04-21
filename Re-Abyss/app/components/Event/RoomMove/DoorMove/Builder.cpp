#include <abyss/components/Event/RoomMove/DoorMove/Builder.hpp>

#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>

#include <abyss/components/Event/RoomMove/RoomMoveCtrl.hpp>
#include <abyss/components/Event/RoomMove/DoorMove/RoomMoveCallback.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::RoomMove::DoorMove
{
    void Builder::Build(
        EventObj* pEvent,
        const Room::RoomData& nextRoom,
        const Actor::Gimmick::Door::DoorData& door,
        const s3d::Vec2& playerPos,
        std::function<void()> fadeInCallback,
        double milliSec
    ) {
        assert(milliSec > 0);

        // 移動制御
        {
            auto manager = pEvent->getManager();

            const auto& current = manager->getModule<RoomManager>()->currentRoom();
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
                ->attach<RoomMoveCtrl>(pEvent, std::move(callback), nextRoom, milliSec);
        }
    }

}
