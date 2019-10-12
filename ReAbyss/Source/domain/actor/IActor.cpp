#include "IActor.hpp"

namespace abyss
{
	void IActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
	void IActor::initView()
	{
		if (auto view = this->createView()) {
			view->setWorld(m_pWorld);
			view->start();
			m_view = std::move(view);
		}
	}
}