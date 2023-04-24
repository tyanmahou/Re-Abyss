#include <abyss/components/Event/RoomMove/DoorMove/RoomMoveCallback.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::RoomMove::DoorMove
{
    RoomMoveCallback::RoomMoveCallback(
        EventObj* pEvent,
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
        auto* camera = m_pEvent->getModule<Camera>();
        m_fade = m_pEvent->getModule<Fader>()
            ->fadeOutIrisOut(camera->transform(m_playerMove.first));
    }

    void RoomMoveCallback::onMoveUpdate(double t)
    {
        m_elapsed = t;

        if (m_state == State::FadeOut) {
            if (t >= 0.5) {
                m_state = State::FadeIn;

                auto* camera = m_pEvent->getModule<Camera>();
                m_fade = m_pEvent->getModule<Fader>()
                    ->fadeInIrisOut(camera->transform(m_playerMove.second));

                // ドア移動の場合はライトを即切り替え
                if(auto&& next = m_pEvent->getModule<RoomManager>()->nextRoom()) {
                    m_pEvent->getModule<Light>()->initColor(next->getLightColor());
                }
                if (this->m_fadeInCallback) {
                    this->m_fadeInCallback();
                }
            }
        }

        if (m_fade) {
            bool isFadeOut = m_state == State::FadeOut;
            auto pos = isFadeOut ? m_playerMove.first : m_playerMove.second;
            auto* camera = m_pEvent->getModule<Camera>();
            m_fade->setPos(camera->transform(pos));
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
