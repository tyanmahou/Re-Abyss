#pragma once
#include <abyss/controllers/Camera/CameraWork/base/ICameraWork.hpp>

namespace abyss
{
    class RoomMoveCameraWork : public ICameraWork
    {
        std::pair<s3d::Vec2, s3d::Vec2> m_cameraMove;
        std::pair<s3d::Vec2, s3d::Vec2> m_playerMove;
        std::function<void()> m_callback;
    public:
        RoomMoveCameraWork(
            Manager* pManager,
            const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
            const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
            std::function<void()> callback,
            double animeMilliSec
        );
        static std::unique_ptr<RoomMoveCameraWork> Create(
            Manager* pManager,
            const CameraModel& camera,
            const s3d::Vec2& playerPos,
            std::function<void()> callback,
            double milliSec
        );
    protected:
        s3d::Vec2 calcCameraPos() const override;
        s3d::Optional<s3d::Vec2> calcPlayerPos() const override;

        void onEnd() override;
    };
}