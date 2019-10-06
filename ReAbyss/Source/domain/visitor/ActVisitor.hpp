#pragma once
#include <application/util/Visitor.hpp>


namespace abyss
{
	class IActor;

	class PlayerActor;
	class PlayerShotActor;

	class MapActor;
	class FloorActor;
	class PenetrateFloorActor;
	class LadderActor;

	class DoorActor;

	class EnemyActor;
	class SlimeActor;

	using ActVisitorBase = Visitor<
		IActor,

		PlayerActor,
		PlayerShotActor,

		MapActor,
		FloorActor,
		PenetrateFloorActor,
		LadderActor,

		DoorActor,

		EnemyActor,
		SlimeActor
	>;

	class ActVisitor : public ActVisitorBase
	{
	public:
		using ActVisitorBase::Visitor;
		using ActVisitorBase::visit;
	};
}