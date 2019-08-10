#pragma once
#include <Siv3D.hpp>
#include "WorldObject.hpp"
#include "Physics.hpp"
#include "Forward.hpp"

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
			Damge
		};
	private:
		Physics m_body;
		int32 m_hp;
		Motation m_motation;
		Forward m_forward;
	public:
		PlayerModel();
		void setPos(const Vec2& pos);
		const Vec2& getPos() const;
		const Vec2& getVellocity() const;
		void update(double dt) override;
		void draw() const override;

		Motation getMotion() const;
		Forward getForward() const;
		Shape getCollider() const override;
	};
}