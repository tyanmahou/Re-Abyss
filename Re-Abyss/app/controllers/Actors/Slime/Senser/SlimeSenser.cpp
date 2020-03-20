#include "SlimeSenser.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/debug/DebugManager/DebugManager.hpp>

namespace abyss
{
	void SlimeSenser::update([[maybe_unused]]double dt)
	{
		if (!m_isActive) {
			return;
		}
		if (!m_onCollision && m_parent->isWalk()) {
			m_parent->getBody().reversed();
		}
		auto isLeft = m_parent->getForward() == Forward::Left;
		if (isLeft) {
			m_pos = m_parent->getPos() + Vec2{ -20, 20 };
		} else {
			m_pos = m_parent->getPos() + Vec2{ 20, 20 };
		}

		m_onCollision = false;
	}

	void SlimeSenser::draw() const
	{
#if ABYSS_DEBUG
		if (DebugManager::IsDrawColider()) {
			Circle(m_pos, 10).draw(ColorF(1, 0, 0, 0.5));
		}
#endif
	}

	CShape SlimeSenser::getCollider() const
	{
		return m_pos;
	}

	void SlimeSenser::onCollisionStay(ICollider* col)
	{
		col->accept([this](MapActor&) {
			m_onCollision = true;
		});
	}

}
