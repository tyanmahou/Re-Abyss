#pragma once

#include <abyss/components/Events/RoomMove/IRoomMoveCallback.hpp>

namespace abyss::Event::RoomMove::BasicMove
{
    class RoomMoveCallback : public IRoomMoveCallback
    {
    public:
        RoomMoveCallback(
            const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
            const std::pair<s3d::Vec2, s3d::Vec2>& playerMove
        );

        void onMoveStart() override;
        void onMoveUpdate(double t) override;
        void onMoveEnd() override;

        s3d::Vec2 calcCameraPos() const override;
        s3d::Vec2 calcPlayerPos() const override;

    private:
        double m_elapsed = 0.0;
        std::pair<s3d::Vec2, s3d::Vec2> m_cameraMove;
        std::pair<s3d::Vec2, s3d::Vec2> m_playerMove;
    };
}