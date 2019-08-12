#include "GameCamera.hpp"
#include "../common/Constants.hpp"
#include "../util/ScopedState.hpp"

#include <Siv3D/Easing.hpp>
#include <Siv3D/Math.hpp>

using namespace s3d;

namespace abyss
{
	GameCamera* GameCamera::m_main = nullptr;

	double GameCamera::elapsed() const
	{
		return s3d::Min<double>(m_animation.ms(), m_animeMilliSec) / m_animeMilliSec;
	}

	GameCamera::GameCamera()
	{
		m_main = this;
	}


	void GameCamera::update(const s3d::Vec2 pos)
	{
		if (this->isCameraWork()) {
			Vec2 origin = m_currentRoom.cameraBorderAdjusted(m_pos);
			m_pos = Easing::EaseIn(origin, m_movePos, Easing::Linear, this->elapsed());

			if (m_animation.ms() >= m_animeMilliSec) {
				m_animation.reset();
				if (this->m_callback) {
					this->m_callback();
				}
				m_playerMovePos = s3d::none;
			}
		}
		else {
			this->setPos(pos);
		}
		m_pos = Math::Ceil(m_pos);
	}
	void GameCamera::adjustPos(s3d::Vec2& pos)
	{
		if (this->isCameraWork() && m_playerMovePos) {
			pos = Easing::EaseIn(m_playerMovePos->first, m_playerMovePos->second, Easing::Linear, this->elapsed());
		}
		else {
			pos = carentRoom().borderAdjusted(pos);
		}
	}
	GameCamera& GameCamera::startCameraWork(const Vec2& pos, std::function<void()> callback, double milliSec)
	{
		assert(milliSec > 0);

		m_animation.restart();
		m_movePos = pos;
		m_callback = callback;
		m_animeMilliSec = milliSec;
		return *this;
	}
	GameCamera& GameCamera::startCameraWork(const Room& nextRoom, std::function<void()> callback, double milliSec)
	{
		Vec2 pos = nextRoom.cameraBorderAdjusted(m_pos);
		if (!callback) {
			callback = [this, nextRoom]() {
				this->setRoom(nextRoom);
			};
		}
		return this->startCameraWork(pos, callback, milliSec);
	}
	bool GameCamera::withPlayerPos(const Vec2& currentPos)
	{
		if (!this->isCameraWork()) {
			return false;
		}
		Vec2 target = currentPos;
		Vec2 v = m_movePos - m_pos;
		bool isHorizontal = Math::Abs(v.x) > Math::Abs(v.y);
		auto border = m_currentRoom.borders();

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
		m_playerMovePos = std::make_pair(currentPos, target);
		return true;
	}
	void GameCamera::setRoom(const Room& room)
	{
		m_currentRoom = room;
	}
	void GameCamera::setPos(const s3d::Vec2 pos)
	{
		m_pos = m_currentRoom.cameraBorderAdjusted(pos);
	}
	const s3d::Vec2& GameCamera::getPos() const
	{
		return m_pos;
	}
	s3d::Rect GameCamera::screenRegion() const
	{
		return s3d::RectF{ m_pos - Constants::GameScreenSize / 2, Constants::GameScreenSize };
	}
	abyss::Transformer2D GameCamera::getTransformer() const
	{
		return Transformer2D(s3d::Mat3x2::Translate(-m_pos).translate(Constants::GameScreenSize / 2 + Constants::GameScreenOffset));
	}
	const Room & GameCamera::carentRoom() const
	{
		return m_currentRoom;
	}
	bool GameCamera::isCameraWork() const
	{
		return m_animation.isActive();
	}
	GameCamera* const GameCamera::Main()
	{
		return GameCamera::m_main;
	}
}