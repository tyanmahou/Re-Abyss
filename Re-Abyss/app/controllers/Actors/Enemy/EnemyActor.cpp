#include "EnemyActor.hpp"
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
#include <abyss/types/CShape.hpp>

namespace abyss::Actor::Enemy
{
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
	const Body& EnemyActor::getBody() const
	{
		return *m_body;
	}
	Body& EnemyActor::getBody()
	{
		return *m_body;
	}
	const HP& EnemyActor::getHp() const
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
