#pragma once

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

namespace abyss
{
	class EnemyActor : public IActor
	{
	protected:
		BodyModel m_body;
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