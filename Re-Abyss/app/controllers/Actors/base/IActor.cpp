#include "IActor.hpp"

namespace abyss
{
    bool IActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
}