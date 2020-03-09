#pragma once

#include <abyss/models/actors/base/IActor.hpp>
#include <abyss/types/Physics.hpp>

namespace abyss
{
	class EnemyActor : public IActor
	{
	protected:
		Physics m_body;
		s3d::int32 m_hp;
	public:
		EnemyActor() = default;

		EnemyActor(const s3d::Vec2& pos, Forward forward = Forward::Left);

		const s3d::Vec2& getPos()const;
		const s3d::Vec2& getVellocity()const;

		Forward getForward()const;
		void accept(const ActVisitor& visitor) override;
	};
}