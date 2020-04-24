#include "Senser.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Actors/Slime/SlimeActor.hpp>

namespace abyss::Slime
{
	void Senser::update([[maybe_unused]]double dt)
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

	void Senser::draw() const
	{
	}

	CShape Senser::getCollider() const
	{
		return m_pos;
	}

	void Senser::onCollisionStay(ICollider* col)
	{
		col->accept([this](MapActor&) {
			m_onCollision = true;
		});
	}

}
