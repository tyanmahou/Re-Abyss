﻿#pragma once

#include <Siv3D.hpp>

#include <abyss/models/actors/base/IActor.hpp>
#include <abyss/types/Physics.hpp>
#include <abyss/views/actors/Player/PlayerView.hpp>

#include "LadderState.hpp"

namespace abyss
{
	class PlayerActor: 
		public IActor,
		public PlayerView
	{
	public:
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
		Physics m_body;
		int32 m_hp;
		Motion m_motion;

		int32 m_charge;
		LadderState m_ladderState;
		bool attack();
		void nomarlMove();
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

		static std::shared_ptr<PlayerActor> Create();
	};
}