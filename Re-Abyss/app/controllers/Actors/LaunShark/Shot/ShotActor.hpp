#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>
#include <abyss/views/Actors/LaunShark/Shot/ShotVM.hpp>

namespace abyss::LaunShark::Shot
{
	class ShotActor :
		public IActor,
		public Attacker,
		public Receiver
	{
	public:
		enum State
		{
			Wait,
			Pursuit,
			Firinged,
		};
	private:
		BodyModel m_body;
		RotateModel m_rotate;
		HPModel m_hp;
		StateManager<ShotActor> m_state;
		std::shared_ptr<ShotVM> m_view;
	public:
		ShotActor(const s3d::Vec2& pos, Forward forward);
		void start() override;
		void update(double dt) override;
		CShape getCollider() const override;
		void onCollisionStay(ICollider* col) override;

		s3d::Quad getColliderQuad() const;

		bool accept(const ActVisitor& visitor) override;
		void draw() const override;

		ShotVM* getBindedView()const;
	};
}