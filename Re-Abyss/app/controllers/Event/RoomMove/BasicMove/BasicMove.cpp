#include "BasicMove.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/Camera/Camera.hpp>

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

    std::shared_ptr<BasicMove> BasicMove::Create(Camera & camera, const s3d::Vec2 & playerPos, double milliSec)
    {
        const auto& current = camera.getCurrentRoom();
        const auto& next = camera.nextRoom();
        Vec2 cameraPos = camera.getPos();

        Vec2 from = current.cameraBorderAdjusted(cameraPos);
        Vec2 to = next->cameraBorderAdjusted(cameraPos);

        // プレイヤーの位置計算
        Vec2 target = playerPos;
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
        return std::make_shared<BasicMove>(
            std::make_pair(from, to),
            std::make_pair(playerPos, target),
            milliSec
            );
    }

    s3d::Vec2 BasicMove::calcCameraPos() const
    {
        return EaseIn(Easing::Linear, m_cameraMove.first, m_cameraMove.second, this->elapsed());
    }

    s3d::Optional<s3d::Vec2> BasicMove::calcPlayerPos() const
    {
        return  EaseIn(Easing::Linear, m_playerMove.first, m_playerMove.second, this->elapsed());
    }

}
