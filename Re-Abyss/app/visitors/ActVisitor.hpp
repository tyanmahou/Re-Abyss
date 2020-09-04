#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Visitor.hpp>

namespace abyss
{

	using ActVisitorBase = Visitor<
		IActor,
		Attacker,
		Receiver,

		Actor::Player::PlayerActor,

		Actor::Enemy::EnemyActor,

		Actor::Map::MapActor,
		Actor::Map::Floor::FloorActor,
		Actor::Map::PenetrateFloor::PenetrateFloorActor,
		Actor::Map::Ladder::LadderActor,

		Actor::Gimmick::Door::DoorActor
	>;

	class ActVisitor : protected ActVisitorBase
	{
	public:
		using ActVisitorBase::Visitor;

		using ActVisitorBase::visit;

		using ActVisitorBase::operator=;
	};
}