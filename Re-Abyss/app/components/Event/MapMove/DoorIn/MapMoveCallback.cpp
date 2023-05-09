#include <abyss/components/Event/MapMove/DoorIn/MapMoveCallback.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Fade/FadeUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::MapMove::DoorIn
{
    MapMoveCallback::MapMoveCallback(
        EventObj* pEvent,
        const s3d::Vec2& cameraMove,
        const s3d::Vec2& playerMove,
        const s3d::Vec2& origin
    ):
        m_pEvent(pEvent),
        m_cameraMove(cameraMove),
        m_playerMove(playerMove),
        m_origin(origin)
    {
    }
    void MapMoveCallback::onMoveStart()
    {
        FadeUtil::OutIrisOut(m_pEvent, m_origin);
    }
    void MapMoveCallback::onMoveUpdate(double t)
    {
        m_elapsed = t;
    }
    void MapMoveCallback::onMoveEnd()
    {
    }
    s3d::Vec2 MapMoveCallback::calcCameraPos() const
    {
        return m_cameraMove;
    }
    s3d::Vec2 MapMoveCallback::calcPlayerPos() const
    {
        return EaseOut(Easing::Circ, m_origin, m_playerMove, Min(1.0, m_elapsed * 1.5));
    }
}

