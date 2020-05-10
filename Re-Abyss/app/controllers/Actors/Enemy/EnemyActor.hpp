#pragma once

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>

namespace abyss
{
	inline namespace Enemy
	{
		class EnemyActor :
			public IActor,
			public Attacker,
			public Receiver
		{
		protected:
			Ref<BodyModel> m_body;
			Ref<HPModel> m_hp;
		public:
			EnemyActor() = default;

			EnemyActor(const s3d::Vec2& pos, Forward forward = Forward::Left);

			void start() override;
			const s3d::Vec2& getPos()const;
			const s3d::Vec2& getVelocity()const;

			Forward getForward()const;
			bool accept(const ActVisitor& visitor) override;

			const BodyModel& getBody()const;
			BodyModel& getBody();
			const HPModel& getHp()const;
			CShape getCollider() const;
			s3d::RectF region()const;
		};
	}
}