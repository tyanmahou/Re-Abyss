#include "EnemyModel.hpp"
#include <domain/visitor/WorldVisitor.hpp>

namespace abyss
{
	EnemyModel::EnemyModel(const s3d::Vec2& pos, Forward forward)
	{
		m_body.pos = pos;
		m_body.forward = forward;
		this->tag = U"enemy";
	}
	const s3d::Vec2& EnemyModel::getPos() const
	{
		return m_body.pos;
	}
	const s3d::Vec2& EnemyModel::getVellocity() const
	{
		return m_body.vellocity;
	}
	Forward EnemyModel::getForward() const
	{
		return m_body.forward;
	}
	void EnemyModel::accept(const WorldVisitor& visitor)
	{
		visitor.visit(*this);
	}
}
