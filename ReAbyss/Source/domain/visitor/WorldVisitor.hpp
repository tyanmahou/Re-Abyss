#pragma once
#include <application/util/Visitor.hpp>


namespace abyss
{
	class WorldObject;

	class PlayerModel;
	class PlayerShotModel;

	class MapModel;
	class FloorModel;
	class PenetrateFloorModel;
	class LadderModel;

	class DoorModel;

	class EnemyModel;
	class SlimeModel;

	using WorldVisitorBase = Visitor<
		WorldObject,

		PlayerModel,
		PlayerShotModel,

		MapModel,
		FloorModel,
		PenetrateFloorModel,
		LadderModel,

		DoorModel,

		EnemyModel,
		SlimeModel
	>;

	class WorldVisitor : public WorldVisitorBase
	{
	public:
		using WorldVisitorBase::Visitor;
		using WorldVisitorBase::visit;
	};
}