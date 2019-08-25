#include "CameraWork.hpp"

namespace abyss
{
	ICameraWork::ICameraWork(double animeMilliSec):
	m_animation(true),
		m_animeMilliSec(animeMilliSec)
	{}

	Optional<Vec2> ICameraWork::calcPlayerPos() const
	{
		return s3d::none;
	}
	bool ICameraWork::isEnd() const
	{
		return m_animation.ms() >= m_animeMilliSec;
	}
	double ICameraWork::elapsed() const
	{
		return s3d::Min<double>(m_animation.ms(), m_animeMilliSec) / m_animeMilliSec;
	}

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

	Vec2 RoomMoveCameraWork::calcCameraPos() const
	{
		return Easing::EaseIn(m_cameraMove.first, m_cameraMove.second, Easing::Linear, this->elapsed());
	}
	Optional<Vec2> RoomMoveCameraWork::calcPlayerPos() const
	{
		return  Easing::EaseIn(m_playerMove.first, m_playerMove.second, Easing::Linear, this->elapsed());
	}

	void RoomMoveCameraWork::onEnd()
	{
		if (this->m_callback) {
			this->m_callback();
		}
	}

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
		m_fadeOutCallback(fadeOutCallback)
	{}

	Vec2 DoorCameraWork::calcCameraPos() const
	{
		return m_state == State::FadeOut ? m_cameraMove.first : m_cameraMove.second;
	}
	Optional<Vec2> DoorCameraWork::calcPlayerPos() const
	{
		return m_state == State::FadeOut ?
			Easing::EaseOut(m_origin, m_playerMove.first, Easing::Circ, Min(1.0, this->fadeOut0_1() * 1.5))
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
	void DoorCameraWork::onEnd()
	{
		if (this->m_fadeOutCallback) {
			this->m_fadeOutCallback();
		}
	}
}
