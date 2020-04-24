#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Player/Shot/PlayerShotModel.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss::Player::Shot
{
	class ShotVM;

	class ShotActor : 
		public IActor,
		public Attacker
	{
	public:
		enum State
		{
			Base,
		};
	private:
		PlayerShotModel m_shot;
		BodyModel m_body;
		StateManager<ShotActor> m_state;
		std::shared_ptr<ShotVM> m_view;
	public:
		ShotActor(const s3d::Vec2& pos, Forward forward, double charge);
		void start() override;
		void update(double dt) override;
		CShape getCollider() const override;
		void onCollisionStay(ICollider* col) override;

		s3d::Circle getColliderCircle() const;

		bool accept(const ActVisitor& visitor) override;
		void draw() const override;

		ShotVM* getBindedView()const;
	};
}