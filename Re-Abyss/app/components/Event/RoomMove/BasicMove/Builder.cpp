#include <abyss/components/Event/RoomMove/BasicMove/Builder.hpp>

#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>

#include <abyss/components/Event/RoomMove/RoomMoveCtrl.hpp>
#include <abyss/components/Event/RoomMove/BasicMove/RoomMoveCallback.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::RoomMove::BasicMove
{
    void Builder::Build(EventObj* pEvent, const RoomData& nextRoom, double milliSec)
    {
        {
            auto* player = pEvent->getModule<Actor::Player::PlayerManager>();
            const auto& pos = player->getPos();
            const auto& current = pEvent->getModule<RoomManager>()->currentRoom();
            auto camera = pEvent->getModule<Camera>();
            Vec2 cameraPos = camera->getPos();

            Vec2 from = current.cameraBorderAdjusted(cameraPos);
            Vec2 to = nextRoom.cameraBorderAdjusted(cameraPos);

            // プレイヤーの位置計算
            Vec2 target = pos;
            Vec2 v = to - from;

            bool isHorizontal = Math::Abs(v.x) > Math::Abs(v.y);
            auto border = current.borders();
            if (isHorizontal) {
                if (v.x > 0) {
                    target.x = border.right + 40;
                } else {
                    target.x = border.left - 40;
                }
            } else {
                if (v.y > 0) {
                    target.y = border.down + 40;
                } else {
                    target.y = border.up - 40;
                }
            }
            auto callback = std::make_unique<RoomMoveCallback>(
                std::make_pair(from, to),
                std::make_pair(pos, target)
                );

            pEvent->attach<RoomMoveCtrl>(pEvent, std::move(callback), nextRoom, milliSec);
        }

    }
}