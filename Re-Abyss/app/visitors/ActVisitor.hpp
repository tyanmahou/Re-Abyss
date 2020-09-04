#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Visitor.hpp>

namespace abyss
{

	using ActVisitorBase = Visitor<
		IActor,
		Attacker,
		Receiver,

		Player::PlayerActor,

		Enemy::EnemyActor,

		Map::MapActor,
		Map::Floor::FloorActor,
		Map::PenetrateFloor::PenetrateFloorActor,
		Map::Ladder::LadderActor,

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