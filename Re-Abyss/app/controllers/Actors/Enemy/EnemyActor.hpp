#pragma once

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>

namespace abyss
{
	class EnemyActor : 
		public IActor,
		public Attacker,
		public Receiver
	{
	protected:
		BodyModel m_body;
		HPModel m_hp;
	public:
		EnemyActor() = default;

		EnemyActor(const s3d::Vec2& pos, Forward forward = Forward::Left);

		void start() override;
		const s3d::Vec2& getPos()const;
		const s3d::Vec2& getVellocity()const;

		Forward getForward()const;
		bool accept(const ActVisitor& visitor) override;

		const BodyModel& getBody()const;
		BodyModel& getBody();

		CShape getCollider() const override;
		s3d::RectF region()const;

		void onCollisionEnter(ICollider* col) override;

		virtual void onDead();
	};
}