#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Visitor.hpp>

namespace abyss::Actor
{

	using ActVisitorBase = Visitor<
		IActor,
		Receiver,

		Player::PlayerActor,

		Enemy::EnemyActor,

		Map::MapActor,
		Map::Floor::FloorActor,
		Map::PenetrateFloor::PenetrateFloorActor,
		Map::Ladder::LadderActor,

		Gimmick::Door::DoorActor
	>;

	class ActVisitor : protected ActVisitorBase
	{
	public:
		using ActVisitorBase::Visitor;

		using ActVisitorBase::visit;

		using ActVisitorBase::operator=;
	};
}