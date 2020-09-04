#include "BasicMove.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>

#include <abyss/controllers/Event/Events.hpp>
namespace abyss::Event::RoomMove
{
    BasicMove::BasicMove(
        const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
        const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
        double animeMilliSec
    ):
        IRoomMove(animeMilliSec),
        m_cameraMove(cameraMove),
        m_playerMove(playerMove)
    {}

    bool BasicMove::Start(const Actor::Player::PlayerActor& player, const RoomModel& nextRoom, double milliSec)
    {
        const auto& pos = player.getPos();
        auto camera = player.getModule<Camera>();
        camera->setNextRoom(nextRoom);

        const auto& current = camera->getCurrentRoom();
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
        auto event = std::make_shared<BasicMove>(
            std::make_pair(from, to),
            std::make_pair(pos, target),
            milliSec
            );

        player.getModule<Events>()->regist(event);
        return true;
    }

    s3d::Vec2 BasicMove::calcCameraPos() const
    {
        return EaseIn(Easing::Linear, m_cameraMove.first, m_cameraMove.second, this->elapsed());
    }

    s3d::Vec2 BasicMove::calcPlayerPos() const
    {
        return  EaseIn(Easing::Linear, m_playerMove.first, m_playerMove.second, this->elapsed());
    }

}
