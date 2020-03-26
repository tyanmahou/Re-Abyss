#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Visitor.hpp>

namespace abyss
{

	using ActVisitorBase = Visitor<
		IActor,
		Attacker,
		Receiver,

		PlayerActor,
		PlayerShotActor,

		EnemyActor,
		SlimeActor,

		MapActor,
		FloorActor,
		PenetrateFloorActor,
		LadderActor,

		DoorActor
	>;

	class ActVisitor : protected ActVisitorBase
	{
	public:
		using ActVisitorBase::Visitor;

		using ActVisitorBase::visit;

		using ActVisitorBase::operator=;
	};
}