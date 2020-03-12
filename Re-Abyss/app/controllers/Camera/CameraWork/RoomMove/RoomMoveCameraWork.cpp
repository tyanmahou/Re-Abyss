#include "RoomMoveCameraWork.hpp"
#include <Siv3D.hpp>

#include <abyss/models/Camera/CameraModel.hpp>

namespace abyss
{
    RoomMoveCameraWork::RoomMoveCameraWork(
        const std::pair<Vec2, Vec2>& cameraMove,
        const std::pair<Vec2, Vec2>& playerMove,
        std::function<void()> callback,
        double animeMilliSec
    ) :
        ICameraWork(animeMilliSec),
        m_cameraMove(cameraMove),
        m_playerMove(playerMove),
        m_callback(callback)
    {}

    std::unique_ptr<RoomMoveCameraWork> RoomMoveCameraWork::Create(
        const CameraModel& camera,
        const s3d::Vec2& playerPos,
        std::function<void()> callback,
        double milliSec
    )
    {
        const auto& current = camera.currentRoom();
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
        return std::make_unique<RoomMoveCameraWork>(
            std::make_pair(from, to),
            std::make_pair(playerPos, target),
            callback,
            milliSec
            );
    }

    Vec2 RoomMoveCameraWork::calcCameraPos() const
    {
        return EaseIn(Easing::Linear, m_cameraMove.first, m_cameraMove.second, this->elapsed());
    }
    Optional<Vec2> RoomMoveCameraWork::calcPlayerPos() const
    {
        return  EaseIn(Easing::Linear, m_playerMove.first, m_playerMove.second, this->elapsed());
    }

    void RoomMoveCameraWork::onEnd()
    {
        if (this->m_callback) {
            this->m_callback();
        }
    }
}