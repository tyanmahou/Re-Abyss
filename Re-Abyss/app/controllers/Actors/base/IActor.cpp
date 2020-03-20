#include "IActor.hpp"

namespace abyss
{
    void IActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
}