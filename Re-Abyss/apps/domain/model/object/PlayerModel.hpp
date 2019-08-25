#pragma once
#include <Siv3D.hpp>
#include "WorldObject.hpp"
#include "../../../application/types/Physics.hpp"
#include "../../../application/util/Collision.hpp"

namespace abyss
{
	class FloorModel;
	class LadderModel;
	class DoorModel;
	class PenetrateFloorModel;

	// íÚéqèÛë‘
	struct LadderState
	{
		enum State
		{
			None = 0x0,
			IsLadder = 0x1,
			IsLadderTop = 0x3,
			CanLadder = 0x4,
		}state;

		LadderState(State s) :
			state(s)
		{}

		void setIsLadder()
		{
			state = static_cast<State>(state | IsLadder);
		}
		bool isLadder() const
		{
			return (state & IsLadder) != 0;
		}
		void setLadderTop()
		{
			state = static_cast<State>(state | IsLadderTop);
		}
		void cancelLadderTop()
		{
			state = static_cast<State>(state & ~0x2);
		}
		bool isLadderTop() const
		{
			return (static_cast<State>(state & IsLadderTop) == IsLadderTop);
		}
		operator bool() const
		{
			return this->isLadder();
		}
		void setCanLadder()
		{
			state = static_cast<State>(state | CanLadder);
		}
		bool canLadder()const
		{
			return (state & CanLadder) != 0;
		}

		void reset()
		{
			if (!this->isLadder() || !this->canLadder()) {
				state = None;
			}
			state = static_cast<State>(state & ~CanLadder);
		}
	};
	class PlayerModel : public WorldObject
	{
		// class Action;
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

		ColDirection collisionAndUpdateMotation(const RectF& region, ColDirection col);
	public:
		PlayerModel();
		void update(double dt) override;
		Shape getCollider() const override;
		void onCollisionStay(ICollider* col) override;
		void onCollisionStay(FloorModel* col);
		void onCollisionStay(LadderModel* col);
		void onCollisionStay(PenetrateFloorModel* col);
		void onCollisionStay(DoorModel* door);
		void setPos(const Vec2& pos);
		const Vec2& getPos() const;
		const Vec2& getVellocity() const;

		void setMotion(Motion motion);
		Motion getMotion() const;
		Forward getForward() const;

		int32 getCharge() const;

		RectF region() const;
	};
}