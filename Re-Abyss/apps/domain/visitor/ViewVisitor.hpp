#pragma once
#include <application/util/Visitor.hpp>
#include <memory>

namespace abyss
{
	class WorldObject;

	class PlayerModel;
	class PlayerShotModel;

	class SlimeModel;

	using ViewVisitor = ConstVisitor<
		std::shared_ptr<WorldObject>,
		std::shared_ptr<PlayerModel>,
		std::shared_ptr<PlayerShotModel>,
		std::shared_ptr<SlimeModel>
	>;
}
