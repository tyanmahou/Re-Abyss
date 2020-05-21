#include "EnemyActor.hpp"
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Enemy/DamageCallbackModel.hpp>

namespace abyss::Enemy
{
	EnemyActor::EnemyActor(const s3d::Vec2& pos, Forward forward)
	{
		// Body
		{
			(m_body = this->attach<BodyModel>(this))
				->initPos(pos)
				.setForward(forward);
		}
		// HP
		{
			(m_hp = this->attach<HPModel>(this))
				->initHp(1)
				.setInvincibleTime(0.2);

		}

		// Collider
		{
			auto collider = this->attach<CustomColliderModel>(this);
			collider->setColFunc([this] {
				return this->region();
			});
			collider->setLayer(LayerGroup::Enemy);
		}

		// ダメージのコンポーネント
		{
			this->attach<DamageCallbackModel>(this);
		}
		{
			this->attach<AudioSourceModel>(this);
		}
	}
	void EnemyActor::start()
	{}
	const s3d::Vec2& EnemyActor::getPos() const
	{
		return m_body->getPos();
	}
	const s3d::Vec2& EnemyActor::getVelocity() const
	{
		return m_body->getVelocity();
	}
	Forward EnemyActor::getForward() const
	{
		return m_body->getForward();
	}
	bool EnemyActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
	const BodyModel& EnemyActor::getBody() const
	{
		return *m_body;
	}
	BodyModel& EnemyActor::getBody()
	{
		return *m_body;
	}
	const HPModel& EnemyActor::getHp() const
    {
		return *m_hp;
    }
	CShape EnemyActor::getCollider() const
	{
		return  this->region();
	}
	s3d::RectF EnemyActor::region() const
	{
		return m_body->region();
	}
}
