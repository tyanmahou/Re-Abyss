#include <abyss/components/Event/RoomMove/DoorMove/RoomMoveCallback.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/components/Fade/FadeUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::RoomMove::DoorMove
{
    RoomMoveCallback::RoomMoveCallback(
        EventObj* pEvent,
        const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
        const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
        const s3d::Vec2& origin,
        std::function<void()> fadeInCallback,
        double milliSec
    ):
        m_pEvent(pEvent),
        m_cameraMove(cameraMove),
        m_playerMove(playerMove),
        m_origin(origin),
        m_fadeInCallback(fadeInCallback),
        m_milliSec(milliSec)
    {
        m_fiber.reset(std::bind(&RoomMoveCallback::updateAsync, this));
    }


    void RoomMoveCallback::onMoveStart()
    {
    }

    void RoomMoveCallback::onMoveUpdate(double t)
    {
        m_elapsed = t;
        m_fiber.resume();
    }

    void RoomMoveCallback::onMoveEnd()
    {
    }

    s3d::Vec2 RoomMoveCallback::calcCameraPos() const
    {
        return m_state == State::FadeOut ?
            m_cameraMove.first
            : m_cameraMove.second;
    }

    s3d::Vec2 RoomMoveCallback::calcPlayerPos() const
    {
        return m_state == State::FadeOut ?
            EaseOut(Easing::Circ, m_origin, m_playerMove.first, Min(1.0, this->fadeOut0_1() * 1.5))
            : m_playerMove.second;
    }
    Coro::Fiber<> RoomMoveCallback::updateAsync()
    {
        // フェードアウト
        m_state = State::FadeOut;
        {
            co_await FadeOut::WaitIrisOut(m_pEvent, m_playerMove.first, m_milliSec / 2000.0);
        }

        // フェードイン
        m_state = State::FadeIn;
        {
            // ドア移動の場合はライトを即切り替え
            if (auto&& next = m_pEvent->getModule<RoomManager>()->nextRoom()) {
                m_pEvent->getModule<Light>()->initColor(next->getLightColor());
            }
            if (this->m_fadeInCallback) {
                this->m_fadeInCallback();
            }

            co_await FadeIn::WaitIrisOut(m_pEvent, m_playerMove.second, m_milliSec / 2000.0);
        }
        co_return;
    }
}
