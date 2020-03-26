#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Player/Shot/PlayerShotModel.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
	class PlayerShotActor : 
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
		StateManager<PlayerShotActor> m_state;
		std::shared_ptr<PlayerShotVM> m_view;
	public:
		PlayerShotActor(const s3d::Vec2& pos, Forward forward, double charge);
		void start() override;
		void update(double dt) override;
		CShape getCollider() const override;
		void onCollisionStay(ICollider* col) override;

		s3d::Circle getColliderCircle() const;

		void accept(const ActVisitor& visitor) override;
		void draw() const override;

		PlayerShotVM* getBindedView()const;
	};
}