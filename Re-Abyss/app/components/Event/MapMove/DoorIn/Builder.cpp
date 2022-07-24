#include <abyss/components/Event/MapMove/DoorIn/Builder.hpp>
#include <abyss/components/Event/Common/FadeIrisOut.hpp>
#include <abyss/components/Event/MapMove/MapMoveCtrl.hpp>
#include <abyss/components/Event/MapMove/DoorIn/MapMoveCallback.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

namespace abyss::Event::MapMove::DoorIn
{
    void Builder::Build(
        EventObj* pEvent,
        const Actor::Gimmick::Door::DoorData& door,
        const s3d::String& link,
        const s3d::Vec2& playerPos,
        double milliSec
    ) {
        assert(milliSec > 0);

        // 移動制御
        {
            auto manager = pEvent->getManager();

            const auto& current = manager->getModule<RoomManager>()->currentRoom();
            Vec2 playerFrom = door.fixedVisiterPos();
            Vec2 from = current.cameraBorderAdjusted(playerFrom);

            auto callback = std::make_unique<MapMoveCallback>(
                pEvent,
                from,
                playerFrom,
                playerPos
                );

            LinkData linkData{
                link,
                door.getStartId()
            };
            pEvent
                ->attach<MapMoveCtrl>(pEvent, std::move(callback), linkData, milliSec);
        }
        // フェード
        {
            pEvent->attach<FadeIrisOut>(pEvent);
        }
    }
}
