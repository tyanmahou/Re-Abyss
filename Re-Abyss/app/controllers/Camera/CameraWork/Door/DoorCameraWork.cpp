#include "DoorCameraWork.hpp"
#include <Siv3D.hpp>

#include <abyss/views/Camera/CameraWork/Door/DoorCameraWorkView.hpp>

namespace abyss
{
    DoorCameraWork::DoorCameraWork(
        const std::pair<Vec2, Vec2>& cameraMove,
        const std::pair<Vec2, Vec2>& playerMove,
        const Vec2& origin,
        std::function<void()> fadeInCallback,
        std::function<void()> fadeOutCallback,
        double animeMilliSec
    ) :
        ICameraWork(animeMilliSec),
        m_cameraMove(cameraMove),
        m_playerMove(playerMove),
        m_origin(origin),
        m_fadeInCallback(fadeInCallback),
        m_fadeOutCallback(fadeOutCallback),
        m_view(std::make_unique<DoorCameraWorkView>(this))
    {}

    Vec2 DoorCameraWork::calcCameraPos() const
    {
        return m_state == State::FadeOut ? m_cameraMove.first : m_cameraMove.second;
    }
    Optional<Vec2> DoorCameraWork::calcPlayerPos() const
    {
        return m_state == State::FadeOut ?
            EaseOut(Easing::Circ, m_origin, m_playerMove.first, Min(1.0, this->fadeOut0_1() * 1.5))
            : m_playerMove.second;
    }
    void DoorCameraWork::update()
    {
        if (m_state == State::FadeOut) {
            if (this->elapsed() >= 0.5) {
                m_state = State::FadeIn;
                if (this->m_fadeInCallback) {
                    this->m_fadeInCallback();
                }
            }
        }
    }
    void DoorCameraWork::draw(const Camera* const pCamera) const
    {
        m_view->draw(pCamera);
    }
    void DoorCameraWork::onEnd()
    {
        if (this->m_fadeOutCallback) {
            this->m_fadeOutCallback();
        }
    }
}