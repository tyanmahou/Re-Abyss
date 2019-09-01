#include "WorldObject.hpp"

#include <domain/visitor/WorldVisitor.hpp>

namespace abyss
{
	void WorldObject::accept(const WorldVisitor& visitor)
	{
		visitor.visit(*this);
	}
}