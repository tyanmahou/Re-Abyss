#include "SlimeModel.hpp"
#include "FloorModel.hpp"

#include <application/util/Collision.hpp>
#include <application/common/Constants.hpp>

#include <domain/model/object/PlayerModel.hpp>
#include <domain/usecase/WorldUseCase.hpp>
#include <domain/visitor/WorldVisitor.hpp>

#include <Siv3D.hpp>
namespace abyss
{
	class SlimeModel::Cencer : public WorldObject
	{
		Vec2 m_pos;
		bool m_onCollision = true;
		SlimeModel* m_parent;
	public:
		Cencer(SlimeModel* p):
			m_parent(p)
		{
		}
		void update(double)override
		{
			if (!m_isActive) {
				return;
			}
			if (!m_onCollision && m_parent->getMotion() == SlimeModel::Motion::Walk) {
				m_parent->reverse();
			}
			auto isLeft = m_parent->getForward() == Forward::Left;
			if (isLeft) {
				m_pos = m_parent->getPos() + Vec2{-20, 20};
			}
			else {
				m_pos = m_parent->getPos() + Vec2{ 20, 20 };
			}

			m_onCollision = false;
		}
		CShape getCollider() const override
		{
			return m_pos;
		}

		void onCollisionStay(ICollider* col) override
		{
			if (auto map = dynamic_cast<MapModel*>(col)) {
				m_onCollision = true;
			}
		}
	};
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
		if (!m_cencer) {
			m_cencer = std::make_shared<Cencer>(this);
			m_pWorld->registerObject(m_cencer);
		}
		if (m_body.forward == Forward::Left) {
			m_body.vellocity.x = -1.0f;
		}
		if (m_body.forward == Forward::Right) {
			m_body.vellocity.x = 1.0f;
		}

		m_body.vellocity += m_body.accel;

		// 前方　かつ　半径　100以内
		Vec2 d = m_pWorld->getPlayer()->getPos() - m_body.pos;
		if (m_body.vellocity.x * d.x > 0 && d.length() <= 150 && m_onCollision) {
			m_body.vellocity.y = -5.5;
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

	CShape SlimeModel::getCollider() const
	{
		return this->region();
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

	void SlimeModel::reverse()
	{
		if (m_body.forward == Forward::Left) {
			m_body.forward = Forward::Right;
		}else if (m_body.forward == Forward::Right) {
			m_body.forward = Forward::Left;
		}
	}

	void SlimeModel::accept(const WorldVisitor& visitor)
	{
		visitor.visit(*this);
	}

}