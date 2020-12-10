#include "EnemyActor.hpp"
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
#include <abyss/types/CShape.hpp>

namespace abyss::Actor::Enemy
{
	EnemyActor::EnemyActor(const s3d::Vec2& pos, Forward forward)
	{
		EnemyBuilder builder(this);
		builder
			.setInitPos(pos)
			.setForward(forward)
			;

		m_tag = Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{};
	}
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
