#include "EnemyActor.hpp"

namespace abyss
{
	EnemyActor::EnemyActor(const s3d::Vec2& pos, Forward forward)
	{
		m_body.setPos(pos);
		m_body.setForward(forward);
		this->tag = U"enemy";
	}
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
}
