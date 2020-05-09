#include <abyss/commons/LayerGroup.hpp>
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/Common/EnemyDeadEffect.hpp>

namespace abyss::Enemy
{
	EnemyActor::EnemyActor(const s3d::Vec2& pos, Forward forward):
		m_hp(1, 0.2)
	{
		m_body
			.setPos(pos)
			.setForward(forward);
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
	bool EnemyActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
	const BodyModel& EnemyActor::getBody() const
	{
		return m_body;
	}
	BodyModel& EnemyActor::getBody()
	{
		return m_body;
	}
    const HPModel& EnemyActor::getHp() const
    {
		return m_hp;
    }
	CShape EnemyActor::getCollider() const
	{
		return  this->region();
	}
	s3d::RectF EnemyActor::region() const
	{
		return m_body.region();
	}

    void EnemyActor::onCollisionStay(ICollider* col)
    {
		col->accept([this](const Attacker& attacker) {
			if (m_hp.damage(attacker.getPower()) && m_hp.isDead()) {
				this->destroy();
				this->onDead();
			}
		});
	}
	void EnemyActor::onDead()
	{
		getModule<World>()->addEffect<EnemyDeadEffect>(this->getPos());
	}
}
