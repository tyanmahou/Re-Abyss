#pragma once
#include <abyss/controllers/Event/RoomMove/base/IRoomMove.hpp>

namespace abyss::Event::RoomMove
{
    class BasicMove : public IRoomMove
    {
        std::pair<s3d::Vec2, s3d::Vec2> m_cameraMove;
        std::pair<s3d::Vec2, s3d::Vec2> m_playerMove;
    public:
        BasicMove(
            const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
            const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
            double animeMilliSec
        );

        static std::shared_ptr<BasicMove> Create(Camera& camera, const s3d::Vec2& playerPos, double milliSec = 2000);
    protected:
        s3d::Vec2 calcCameraPos() const override;
        s3d::Optional<s3d::Vec2> calcPlayerPos() const override;

    };
}