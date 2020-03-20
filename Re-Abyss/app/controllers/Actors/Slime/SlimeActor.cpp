#include "SlimeActor.hpp"

#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/Actors/Floor/FloorActor.hpp>
#include <abyss/controllers/World/World.hpp>

#include <abyss/utils/Collision/Collision.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/Actors/Slime/SlimeVM.hpp>

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
			} else {
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
		c.ignoredForVelocity(m_body.getVelocity());

		Vec2 before = this->region().center();
		auto[after, colDir] = collision::Collision(map.region(), this->region(), c);

		m_body.addPos(after - before);

		if (colDir.isUp()) {
			m_onCollision = true;
			m_motion = Motion::Walk;
		}
		if (colDir.isRight()) {
			m_body.setForward(Forward::Right);
		}
		if (colDir.isLeft()) {
			m_body.setForward(Forward::Left);
		}
	}

	SlimeActor::SlimeActor(const s3d::Vec2& pos, Forward forward) :
		EnemyActor(pos, forward),
		m_view(std::make_shared<SlimeVM>())
	{
		m_hp = 10;
		m_onCollision = true;
		m_body.setMaxSpeedX(60);
	}

	void SlimeActor::start()
	{
		if (!m_cencer) {
			m_cencer = std::make_shared<Cencer>(this);
			m_pWorld->regist(m_cencer);
		}
	}

	void SlimeActor::update([[maybe_unused]]double dt)
	{
		if (m_body.getForward() == Forward::Left) {
			m_body.setAccelX(-720.0);
		}
		if (m_body.getForward() == Forward::Right) {
			m_body.setAccelX(720.0f);
		}

		// 前方　かつ　半径　150以内
		Vec2 d = m_pWorld->getPlayer()->getPos() - m_body.getPos();
		if (m_body.getVelocity().x * d.x > 0 && d.length() <= 150 && m_onCollision) {
			m_body.jumpToHeight(80);
		}
		m_body.update(dt);

		if (!m_onCollision) {
			m_motion = Motion::Jump;
		}
		m_onCollision = false;
	}

	void SlimeActor::draw() const
	{
		m_view->bind(*this);
		m_view->drawWalk();
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
			return s3d::RectF(m_body.getPos().x - 35.0 / 2, m_body.getPos().y + 20 -25, 35, 25);
		}
		return s3d::RectF(m_body.getPos().x - 16, m_body.getPos().y - 16, 32, 32);
	}

	SlimeActor::Motion SlimeActor::getMotion() const
	{
		return m_motion;
	}

	void SlimeActor::reverse()
	{
		m_body.reversed();
	}

	void SlimeActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
}