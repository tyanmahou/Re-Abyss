#include "CameraWork.hpp"
#include "CameraModel.hpp"
#include "RoomModel.hpp"
#include <Siv3D.hpp>

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

	std::shared_ptr<RoomMoveCameraWork> RoomMoveCameraWork::Create(
		const CameraModel& camera,
		const s3d::Vec2 & playerPos,
		std::function<void()> callback, 
		double milliSec
	){
		const auto& current = camera.carentRoom();
		const auto& next = camera.nextRoom();
		Vec2 cameraPos = camera.getPos();

		Vec2 from = current.cameraBorderAdjusted(cameraPos);
		Vec2 to = next->cameraBorderAdjusted(cameraPos);

		// プレイヤーの位置計算
		Vec2 target = playerPos;
		Vec2 v = to - from;

		bool isHorizontal = Math::Abs(v.x) > Math::Abs(v.y);
		auto border = current.borders();
		if (isHorizontal) {
			if (v.x > 0) {
				target.x = border.right + 40;
			}
			else {
				target.x = border.left - 40;
			}
		}
		else {
			if (v.y > 0) {
				target.y = border.down + 40;
			}
			else {
				target.y = border.up - 40;
			}
		}
		return std::make_shared<RoomMoveCameraWork>(
			std::make_pair(from, to),
			std::make_pair(playerPos, target),
			callback,
			milliSec
		);
	}

	Vec2 RoomMoveCameraWork::calcCameraPos() const
	{
		return EaseIn(Easing::Linear, m_cameraMove.first, m_cameraMove.second, this->elapsed());
	}
	Optional<Vec2> RoomMoveCameraWork::calcPlayerPos() const
	{
		return  EaseIn(Easing::Linear, m_playerMove.first, m_playerMove.second, this->elapsed());
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
			EaseOut(Easing::Circ, m_origin, m_playerMove.first,  Min(1.0, this->fadeOut0_1() * 1.5))
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
