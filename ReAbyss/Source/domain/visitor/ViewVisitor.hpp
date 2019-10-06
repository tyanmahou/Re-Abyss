#pragma once
#include <application/util/Visitor.hpp>
#include <memory>

namespace abyss
{
	class IActor;

	class PlayerActor;
	class PlayerShotActor;

	class SlimeActor;

	using ViewVisitor = ConstVisitor<
		std::shared_ptr<IActor>,
		std::shared_ptr<PlayerActor>,
		std::shared_ptr<PlayerShotActor>,
		std::shared_ptr<SlimeActor>
	>;
}
