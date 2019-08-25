#pragma once
#include "WorldObject.hpp"

#include <application/types/Physics.hpp>

namespace abyss
{
	class EnemyModel : public WorldObject
	{
	protected:
		Physics m_body;
		s3d::int32 m_hp;
	public:
		EnemyModel() = default;

		EnemyModel(const s3d::Vec2& pos, Forward forward = Forward::Left);

		const s3d::Vec2& getPos()const;
		const s3d::Vec2& getVellocity()const;

		Forward getForward()const;
	};
}