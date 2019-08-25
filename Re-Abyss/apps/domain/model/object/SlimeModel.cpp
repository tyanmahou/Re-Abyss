#include "SlimeModel.hpp"
#include "FloorModel.hpp"

#include <application/util/Collision.hpp>
#include <application/common/Constants.hpp>

#include <domain/model/object/PlayerModel.hpp>
#include <domain/usecase/WorldUseCase.hpp>

#include <Siv3D.hpp>
namespace abyss
{
	void SlimeModel::onCollision(MapModel* map)
	{
		auto c = map->getCol();
		if (m_body.vellocity.y > 0) c &= ~collision::Down;
		if (m_body.vellocity.y < 0) c &= ~collision::Up;
		if (m_body.vellocity.x > 0) c &= ~collision::Right;
		if (m_body.vellocity.x < 0) c &= ~collision::Left;

		Vec2 before = this->region().center;
		auto collision = collision::Collision(map->region(), this->region(), c);

		Vec2 after = collision.first;
		m_body.pos += (after - before);

		if (collision.second & collision::Up) {
			m_onCollision = true;
			m_motion = Motion::Walk;
		}
		if (collision.second & collision::Right) {
			m_body.forward = Forward::Right;
		}
		if (collision.second & collision::Left) {
			m_body.forward = Forward::Left;
		}
	}

	SlimeModel::SlimeModel(const s3d::Vec2& pos, Forward forward) :
		EnemyModel(pos, forward)
	{
		m_hp = 10;
		m_body.accel.y = 0.2;
		m_onCollision = true;
	}

	void SlimeModel::start()
	{
	}

	void SlimeModel::update(double)
	{
		if (m_body.forward == Forward::Left) {
			m_body.vellocity.x = -1.0f;
		}
		if (m_body.forward == Forward::Right) {
			m_body.vellocity.x = 1.0f;
		}

		m_body.vellocity += m_body.accel;

		// 前方　かつ　半径　100以内
		Vec2 d = m_pWorld->getPlayer()->getPos() - m_body.pos;
		if (m_body.vellocity.x * d.x > 0 && d.length() <= 100 && m_onCollision) {
			m_body.vellocity.y = -4;
		}
		if (m_body.vellocity.y > Constants::Player::MaxGravity) {
			m_body.vellocity.y = Constants::Player::MaxGravity;
		}
		m_body.pos += m_body.vellocity;

		if (!m_onCollision) {
			m_motion = Motion::Jump;
		}
		m_onCollision = false;
	}

	void SlimeModel::onCollisionEnter(ICollider* col)
	{
		if (col->getTag() == L"floor" || col->getTag() == L"ladder" || col->getTag() == L"penetrate_floor") {
			auto* map = static_cast<MapModel*>(col);
			this->onCollision(map);
		}
	}

	void SlimeModel::onCollisionStay(ICollider* col)
	{
		if (col->getTag() == L"floor" || col->getTag() == L"ladder" || col->getTag() == L"penetrate_floor") {
			auto* map = static_cast<MapModel*>(col);
			this->onCollision(map);
		}
	}

	s3d::Shape SlimeModel::getCollider() const
	{
		return static_cast<s3d::Shape>(this->region());
	}

	s3d::RectF SlimeModel::region() const
	{
		if (m_motion == Motion::Walk) {
			return s3d::RectF(m_body.pos.x - 35.0 / 2, m_body.pos.y + 20 -25, 35, 25);
		}
		return s3d::RectF(m_body.pos.x - 16, m_body.pos.y - 16, 32, 32);
	}

	SlimeModel::Motion SlimeModel::getMotion() const
	{
		return m_motion;
	}

}