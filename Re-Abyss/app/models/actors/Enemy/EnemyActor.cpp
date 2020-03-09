#include "EnemyActor.hpp"

namespace abyss
{
	EnemyActor::EnemyActor(const s3d::Vec2& pos, Forward forward)
	{
		m_body.pos = pos;
		m_body.forward = forward;
		this->tag = U"enemy";
	}
	const s3d::Vec2& EnemyActor::getPos() const
	{
		return m_body.pos;
	}
	const s3d::Vec2& EnemyActor::getVellocity() const
	{
		return m_body.vellocity;
	}
	Forward EnemyActor::getForward() const
	{
		return m_body.forward;
	}
	void EnemyActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
}
