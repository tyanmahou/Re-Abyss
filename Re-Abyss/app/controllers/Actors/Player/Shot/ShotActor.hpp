#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Player/Shot/PlayerShot.hpp>

namespace abyss::Actor::Player::Shot
{
	class ShotVM;

	class ShotActor : 
		public IActor,
		public Attacker
	{
	public:
		ShotActor(const s3d::Vec2& pos, Forward forward, double charge);

		bool accept(const ActVisitor& visitor) override;
	};
}