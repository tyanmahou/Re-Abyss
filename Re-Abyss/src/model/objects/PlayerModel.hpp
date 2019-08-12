#pragma once
#include <Siv3D.hpp>
#include "../WorldObject.hpp"
#include "../Physics.hpp"

namespace abyss
{
	class PlayerModel : public WorldObject
	{
	public:
		enum class Motation
		{
			Stay,
			Swim,
			Float,
			Dive,
			Damge,
			Ladder,
			LadderTop,
			Shoting
		};
	private:
		Physics m_body;
		int32 m_hp;
		Motation m_motation;

		int32 m_charge;

		bool attack();
	public:
		PlayerModel();
		void update(double dt) override;
		void draw() const override;
		Shape getCollider() const override;
		void onCollisionStay(ICollider* col) override;

		void setPos(const Vec2& pos);
		const Vec2& getPos() const;
		const Vec2& getVellocity() const;

		Motation getMotion() const;
		Forward getForward() const;

		int32 getCharge() const;

		RectF region() const;
	};
}