#pragma once
#include <Siv3D.hpp>
#include "IActor.hpp"
#include "LadderState.hpp"
#include <application/types/Physics.hpp>
#include <application/util/Observable.hpp>
#include <application/util/Collision.hpp>

namespace abyss
{
	class FloorActor;
	class LadderActor;
	class DoorActor;
	class PenetrateFloorActor;

	class PlayerActor : public IActor
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

		// ƒhƒA‚É“ü‚é
		Observable<void(const DoorActor*)> m_onIntoDoor;
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

		inline Observable<void(const DoorActor*)>& onIntoDoor()
		{
			return m_onIntoDoor;
		}

		void accept(const ActVisitor& visitor) override;

		std::unique_ptr<IActorView> createView() const override;

		static std::shared_ptr<PlayerActor> Create();
	};
}