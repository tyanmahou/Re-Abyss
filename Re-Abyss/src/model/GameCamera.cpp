#include "GameCamera.hpp"
#include "../common/Constants.hpp"
#include "../util/ScopedState.hpp"
#include "../view/fade/Fade.hpp"
#include "../model/objects/DoorModel.hpp"

#include <Siv3D/Easing.hpp>
#include <Siv3D/Math.hpp>

using namespace s3d;

namespace abyss
{
	class ICameraWork
	{
	protected:
		s3d::Stopwatch m_animation;
		double m_animeMilliSec = 0;
	public:
		ICameraWork(double animeMilliSec) :
			m_animation(true),
			m_animeMilliSec(animeMilliSec)
		{}
		virtual ~ICameraWork() = default;

		virtual void update() {};
		virtual void draw(const GameCamera* const)const {};
		virtual Vec2 calcCameraPos() const = 0;
		virtual Optional<Vec2> calcPlayerPos() const
		{
			return s3d::none;
		}

		bool isEnd() const
		{
			return m_animation.ms() >= m_animeMilliSec;
		}
		virtual void onEnd() {};

		double elapsed() const
		{
			return s3d::Min<double>(m_animation.ms(), m_animeMilliSec) / m_animeMilliSec;
		}
	};

	class RoomMoveCameraWork : public ICameraWork
	{
		std::pair<Vec2, Vec2> m_cameraMove;
		std::pair<Vec2, Vec2> m_playerMove;
		std::function<void()> m_callback;
	public:
		RoomMoveCameraWork(
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
	protected:
		Vec2 calcCameraPos() const override
		{
			return Easing::EaseIn(m_cameraMove.first, m_cameraMove.second, Easing::Linear, this->elapsed());
		}
		Optional<Vec2> calcPlayerPos() const override
		{
			return  Easing::EaseIn(m_playerMove.first, m_playerMove.second, Easing::Linear, this->elapsed());
		}

		void onEnd() override
		{
			if (this->m_callback) {
				this->m_callback();
			}
		}
	};

	class DoorCameraWork : public ICameraWork
	{
		std::pair<Vec2, Vec2> m_cameraMove;
		std::pair<Vec2, Vec2> m_playerMove;
		Vec2 m_origin;
		std::function<void()> m_fadeInCallback;
		std::function<void()> m_fadeOutCallback;

		enum class State {
			FadeIn,
			FadeOut
		}m_state = State::FadeOut;
	public:
		DoorCameraWork(
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

	protected:

		Vec2 calcCameraPos() const override
		{
			return m_state == State::FadeOut ? m_cameraMove.first : m_cameraMove.second;
		}
		Optional<Vec2> calcPlayerPos() const override
		{
			return m_state == State::FadeOut ? 
				Easing::EaseOut(m_origin, m_playerMove.first, Easing::Circ, Min(1.0, this->fadeOut0_1()*1.5))
				: m_playerMove.second;
		}
		void update() override
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
		void onEnd() override
		{
			if (this->m_fadeOutCallback) {
				this->m_fadeOutCallback();
			}
		}

		void draw(const GameCamera* const camera)const override
		{
			if (m_state == State::FadeIn) {
				FadeIn(Fade::SmoothCircle, fadeIn0_1(),  camera->screenRegion(), m_playerMove.second);
			}
			else {
				FadeOut(Fade::SmoothCircle, fadeOut0_1(),camera->screenRegion(), m_playerMove.first);
			}
		}
	private:
		double fadeIn0_1()const
		{
			return (this->elapsed() - 0.5) / 0.5;
		}
		double fadeOut0_1()const
		{
			return this->elapsed()/ 0.5;
		}
	};

	GameCamera* GameCamera::m_main = nullptr;


	GameCamera::GameCamera()
	{
		m_main = this;
	}


	void GameCamera::update(const s3d::Vec2 pos)
	{
		if (this->isCameraWork()) {
			m_cameraWork->update();
			m_pos = m_cameraWork->calcCameraPos();

			if (m_cameraWork->isEnd()) {
				m_cameraWork->onEnd();
				m_cameraWork = nullptr;
				m_nextRoom = s3d::none;
			}
		}
		else {
			this->setPos(pos);
		}
		m_pos = Math::Ceil(m_pos);
	}
	void GameCamera::adjustPos(s3d::Vec2& pos)
	{
		if (this->isCameraWork()) {
			if (auto playerPos = m_cameraWork->calcPlayerPos()) {
				pos = playerPos.value();
			}
		}
		else {
			pos = carentRoom().borderAdjusted(pos);
		}
	}
	bool GameCamera::isOutOfRoomDeath(const s3d::Vec2& pos) const
	{
		if (!m_currentRoom.passable(Forward::Down) && pos.y > m_currentRoom.borders().down) {
			return true;
		}
		return false;
	}

	void GameCamera::startCameraWork(const Room& nextRoom, const s3d::Vec2& playerPos, std::function<void()> callback, double milliSec)
	{
		assert(milliSec > 0);

		m_nextRoom = nextRoom;

		Vec2 from = m_currentRoom.cameraBorderAdjusted(m_pos);
		Vec2 to = nextRoom.cameraBorderAdjusted(m_pos);
		if (!callback) {
			callback = [this, nextRoom]() {
				this->setRoom(nextRoom);
			};
		}

		// プレイヤーの位置計算
		Vec2 target = playerPos;
		Vec2 v = to - from;

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
		m_cameraWork = std::make_shared<RoomMoveCameraWork>(
			std::make_pair(from, to),
			std::make_pair(playerPos, target),
			callback,
			milliSec
			);
	}

	void GameCamera::startDoorCameraWork(const DoorModel& door, const s3d::Vec2& playerPos, std::function<void()> fadeInCallback, std::function<void()> fadeOutCallback, double milliSec)
	{
		m_nextRoom = door.getNextRoom();
		Vec2 playerFrom = door.fixedVisiterPos();
		Vec2 playerTo = door.getTargetPos();
		Vec2 from = m_currentRoom.cameraBorderAdjusted(playerFrom);
		Vec2 to = m_nextRoom->cameraBorderAdjusted(playerTo);

		if (!fadeOutCallback) {
			fadeOutCallback = [this]() {
				this->setRoom(*m_nextRoom);
			};
		}
		m_cameraWork = std::make_shared<DoorCameraWork>(
			std::make_pair(from, to),
			std::make_pair(playerFrom, playerTo),
			playerPos,
			fadeInCallback,
			fadeOutCallback,
			milliSec
			);
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
	s3d::RectF GameCamera::screenRegion() const
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
		return m_cameraWork != nullptr;
	}
	void GameCamera::drawDeathLine() const
	{
		constexpr Color colors[4] = { ColorF(0,0), ColorF(0,0) ,ColorF(0,1),ColorF(0,1) };
		if (!m_currentRoom.passable(Forward::Down)) {
			auto region = m_currentRoom.getRegion();
			RectF(region.x, region.y + region.size.y - 40, region.w, 40).draw(colors);
		}
		if (m_nextRoom && !m_nextRoom->passable(Forward::Down)) {
			auto region = m_nextRoom->getRegion();
			RectF(region.x, region.y + region.size.y - 40, region.w, 40).draw(colors);
		}
	}
	void GameCamera::drawCameraWork() const
	{
		if (m_cameraWork) {
			m_cameraWork->draw(this);
		}
	}
	GameCamera* const GameCamera::Main()
	{
		return GameCamera::m_main;
	}
}