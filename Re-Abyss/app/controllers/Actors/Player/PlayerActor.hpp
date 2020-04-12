#pragma once

#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/FootModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/models/Actors/Player/ChargeModel.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
	class PlayerActor: 
		public IActor,
		public Receiver
	{
	public:
		enum class State
		{
			Swim,
			Damage,
			Ladder,
		};
	private:
		BodyModel m_body;
		FootModel m_foot;
		ChargeModel m_charge;
		HPModel m_hp;


		StateManager<PlayerActor> m_state;
		std::shared_ptr<PlayerVM> m_view;

	public:
		PlayerActor();
		void update(double dt) override;
		void lastUpdate(double dt) override;

		CShape getCollider() const override;
		void onCollisionStay(ICollider* col) override;
		void setPos(const Vec2& pos);
		const Vec2& getPos() const;
		void setForward(const Forward& forward);

		RectF region() const;

		bool accept(const ActVisitor& visitor) override;
		void draw() const override;
		PlayerVM* getBindedView()const;

		static std::shared_ptr<PlayerActor> Create();
    };
}