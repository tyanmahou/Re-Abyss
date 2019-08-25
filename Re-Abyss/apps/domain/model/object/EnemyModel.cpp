#include "EnemyModel.hpp"

namespace abyss
{
	EnemyModel::EnemyModel(const s3d::Vec2& pos, Forward forward)
	{
		m_body.pos = pos;
		m_body.forward = forward;
		this->tag = L"enemy";
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
}
