#include <abyss/commons/LayerGroup.hpp>
#include <abyss/commons/ActInclude.hpp>

namespace abyss
{
	EnemyActor::EnemyActor(const s3d::Vec2& pos, Forward forward)
	{
		m_body.setPos(pos);
		m_body.setForward(forward);
		this->tag = U"enemy";
		this->layer = LayerGroup::Enemy;
	}
	void EnemyActor::start()
	{}
	const s3d::Vec2& EnemyActor::getPos() const
	{
		return m_body.getPos();
	}
	const s3d::Vec2& EnemyActor::getVellocity() const
	{
		return m_body.getVelocity();
	}
	Forward EnemyActor::getForward() const
	{
		return m_body.getForward();
	}
	void EnemyActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
	const BodyModel& EnemyActor::getBody() const
	{
		return m_body;
	}
	BodyModel& EnemyActor::getBody()
	{
		return m_body;
	}
	CShape EnemyActor::getCollider() const
	{
		return  this->region();
	}
	s3d::RectF EnemyActor::region() const
	{
		return m_body.region();
	}
	void EnemyActor::onCollisionEnter(ICollider* col)
	{
		col->accept([this](const Attacker& attacker) {
			if (m_hp.damage(attacker.getPower()) && m_hp.isDead()) {
				m_isActive = false;
				this->onDead();
			}
		});
	}
	void EnemyActor::onDead()
	{}
}
