#include <abyss/commons/LayerGroup.hpp>
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/Common/EnemyDeadEffect.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
namespace abyss::Enemy
{
	EnemyActor::EnemyActor(const s3d::Vec2& pos, Forward forward)
	{
		// Body
		m_bodyModel = this->addComponent<BodyModel>(this);
		m_bodyModel
			->initPos(pos)
			.setForward(forward);
		m_hpModel = this->addComponent<experimental::HPModel>(this);
		m_hpModel->setHp(1)
			.setInvincibleTime(0.2);

		// Collider
		auto collider = this->addComponent<CustomColliderModel>(this);
		collider->setColFunc([this] {
			return this->region();
		});
		collider->setLayer(LayerGroup::Enemy);
	}
	void EnemyActor::start()
	{}
	const s3d::Vec2& EnemyActor::getPos() const
	{
		return m_bodyModel->getPos();
	}
	const s3d::Vec2& EnemyActor::getVellocity() const
	{
		return m_bodyModel->getVelocity();
	}
	Forward EnemyActor::getForward() const
	{
		return m_bodyModel->getForward();
	}
	bool EnemyActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
	const BodyModel& EnemyActor::getBody() const
	{
		return *m_bodyModel;
	}
	BodyModel& EnemyActor::getBody()
	{
		return *m_bodyModel;
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
		return m_bodyModel->region();
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
