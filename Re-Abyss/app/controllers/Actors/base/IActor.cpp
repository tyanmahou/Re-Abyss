#include "IActor.hpp"

namespace abyss
{
    void IActor::setup()
    {
        m_components.setup();
    }
    void IActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
}