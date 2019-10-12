#include "WorldFacade.hpp"

#include <domain/actor/PlayerActor.hpp>
#include <domain/model/CollisionModel.hpp>

namespace abyss
{
	World::World():
		m_collision(std::make_unique<SimpleCollision>())
	{
		m_worldView.setWorldModel(&m_worldModel);
	}
	void World::update()
	{
		m_worldModel.update();
		// Õ“Ë
		m_collision->collisionAll(m_worldModel.getActors());

		m_worldModel.erase();
	}
	void World::reset()
	{
		m_worldModel.clear();
		m_collision->reset();
		if (m_pPlayer) {
			m_worldModel.pushActor(m_pPlayer);
		}
	}
	void World::draw() const
	{
		m_worldView.draw();
	}
}
