#include <abyss/components/Event/RoomMove/BasicMove/RoomMoveCallback.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::RoomMove::BasicMove
{
    RoomMoveCallback::RoomMoveCallback(
        const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
        const std::pair<s3d::Vec2, s3d::Vec2>& playerMove
    ):
        m_cameraMove(cameraMove),
        m_playerMove(playerMove)
    {}

    void RoomMoveCallback::onMoveStart()
    {
    }

    void RoomMoveCallback::onMoveUpdate(double t)
    {
        m_elapsed = t;
    }

    void RoomMoveCallback::onMoveEnd()
    {
    }

    s3d::Vec2 RoomMoveCallback::calcCameraPos() const
    {
        return EaseIn(Easing::Linear, m_cameraMove.first, m_cameraMove.second, m_elapsed);
    }

    s3d::Vec2 RoomMoveCallback::calcPlayerPos() const
    {
        return  EaseIn(Easing::Linear, m_playerMove.first, m_playerMove.second, m_elapsed);
    }
}
