#include "RoomMoveCallback.hpp"
#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::RoomMove::DoorMove
{
    RoomMoveCallback::RoomMoveCallback(
        IEvent* pEvent,
        const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
        const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
        const s3d::Vec2& origin,
        std::function<void()> fadeInCallback
    ):
        m_pEvent(pEvent),
        m_cameraMove(cameraMove),
        m_playerMove(playerMove),
        m_origin(origin),
        m_fadeInCallback(fadeInCallback)
    {}


    void RoomMoveCallback::onMoveStart()
    {
        m_fade = m_pEvent->find<FadeIrisOut>();
    }

    void RoomMoveCallback::onMoveUpdate(double t)
    {
        m_elapsed = t;

        if (m_state == State::FadeOut) {
            if (t >= 0.5) {
                m_state = State::FadeIn;

                // ドア移動の場合はライトを即切り替え
                if(auto&& next = m_pEvent->getModule<RoomManager>()->nextRoom()) {
                    m_pEvent->getModule<Light>()->initColor(next->getLightColor());
                }
                if (this->m_fadeInCallback) {
                    this->m_fadeInCallback();
                }
            }
        }

        bool isFadeOut = m_state == State::FadeOut;

        if (m_fade) {
            auto pos = isFadeOut ? m_playerMove.first : m_playerMove.second;
            m_fade->setPos(pos)
                .setFadeTime(isFadeOut ? this->fadeOut0_1() : this->fadeIn0_1())
                .setIsFadeIn(!isFadeOut)
                ;
        }
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
}
