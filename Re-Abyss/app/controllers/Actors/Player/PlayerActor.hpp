#pragma once

#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Player/ChargeModel.hpp>
#include <abyss/models/Actors/Player/LadderStateModel.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
	class PlayerActor: 
		public IActor
	{
	public:
		enum class State
		{
			Stay,
			Swim,
			Run,
			Float,
			Dive,
			Damge,
			Ladder,
			LadderTop,
			Door,
			Shoting
		};
		enum class Motion
		{
			Stay,
			Swim,
			Run,
			Float,
			Dive,
			Damge,
			Ladder,
			LadderTop,
			Door,
			Shoting
		};

	private:
		BodyModel m_body;
		int32 m_hp;
		Motion m_motion;

		int32 m_charge;
		LadderStateModel m_ladderState;

		StateManager<PlayerActor> m_state;
		std::shared_ptr<PlayerVM> m_view;

		bool attack();
		void nomarlMove(double dt);
		void ladderMove();

		ColDirection collisionAndUpdateMotion(const RectF& region, ColDirection col);
	public:
		PlayerActor();
		void update(double dt) override;
		CShape getCollider() const override;
		void onCollisionStay(ICollider* col) override;
		void onCollisionStay(const FloorActor& col);
		void onCollisionStay(const LadderActor& col);
		void onCollisionStay(const PenetrateFloorActor& col);
		void onCollisionStay(const DoorActor& door);
		void setPos(const Vec2& pos);
		const Vec2& getPos() const;
		const Vec2& getVellocity() const;

		void setMotion(Motion motion);
		Motion getMotion() const;
		Forward getForward() const;

		int32 getCharge() const;

		RectF region() const;

		void accept(const ActVisitor& visitor) override;
		void draw() const override;
		PlayerVM* getBindedView()const;

		static std::shared_ptr<PlayerActor> Create();
	};
}