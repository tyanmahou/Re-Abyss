#include "SlimeActor.hpp"
#include "FloorActor.hpp"

#include <application/util/Collision.hpp>
#include <application/common/Constants.hpp>

#include <domain/actor/PlayerActor.hpp>
#include <domain/facade/WorldFacade.hpp>

#include <presentation/view/actor/SlimeView.hpp>

#include <Siv3D.hpp>
namespace abyss
{
	class SlimeActor::Cencer : public IActor
	{
		Vec2 m_pos;
		bool m_onCollision = true;
		SlimeActor* m_parent;
	public:
		Cencer(SlimeActor* p):
			m_parent(p)
		{
		}
		void update(double)override
		{
			if (!m_isActive) {
				return;
			}
			if (!m_onCollision && m_parent->getMotion() == SlimeActor::Motion::Walk) {
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
			col->accept([this](MapActor&) {
				m_onCollision = true;
			});
		}
	};
	void SlimeActor::onCollision(const MapActor& map)
	{
		auto c = map.getCol();
		if (m_body.vellocity.y > 0) c &= ~collision::Down;
		if (m_body.vellocity.y < 0) c &= ~collision::Up;
		if (m_body.vellocity.x > 0) c &= ~collision::Right;
		if (m_body.vellocity.x < 0) c &= ~collision::Left;

		Vec2 before = this->region().center();
		auto collision = collision::Collision(map.region(), this->region(), c);

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

	SlimeActor::SlimeActor(const s3d::Vec2& pos, Forward forward) :
		EnemyActor(pos, forward)
	{
		m_hp = 10;
		m_body.accel.y = 0.2;
		m_onCollision = true;
	}

	void SlimeActor::start()
	{
	}

	void SlimeActor::update(double)
	{
		if (!m_cencer) {
			m_cencer = std::make_shared<Cencer>(this);
			m_pWorld->regist(m_cencer);
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

	void SlimeActor::draw() const
	{
	}

	void SlimeActor::onCollisionEnter(ICollider* col)
	{
		col->accept([this](const MapActor& map) {
			this->onCollision(map);
		});
	}

	void SlimeActor::onCollisionStay(ICollider* col)
	{
		col->accept([this](const MapActor& map) {
			this->onCollision(map);
		});
	}

	CShape SlimeActor::getCollider() const
	{
		return this->region();
	}

	s3d::RectF SlimeActor::region() const
	{
		if (m_motion == Motion::Walk) {
			return s3d::RectF(m_body.pos.x - 35.0 / 2, m_body.pos.y + 20 -25, 35, 25);
		}
		return s3d::RectF(m_body.pos.x - 16, m_body.pos.y - 16, 32, 32);
	}

	SlimeActor::Motion SlimeActor::getMotion() const
	{
		return m_motion;
	}

	void SlimeActor::reverse()
	{
		if (m_body.forward == Forward::Left) {
			m_body.forward = Forward::Right;
		}else if (m_body.forward == Forward::Right) {
			m_body.forward = Forward::Left;
		}
	}

	void SlimeActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}

	std::unique_ptr<IActorView> SlimeActor::createView() const
	{
		return std::make_unique<SlimeView>(this);
	}

}