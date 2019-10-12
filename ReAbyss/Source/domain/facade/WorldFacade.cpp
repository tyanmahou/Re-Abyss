#include "WorldFacade.hpp"
#include <domain/usecase/CollisionUseCase.hpp>

namespace abyss
{
	World::World(std::unique_ptr<ICollisionUseCase>&& collision):
		m_collisionUseCase(std::move(collision))
	{
		m_worldView.setWorldModel(&m_worldModel);
	}
	void World::update()
	{
		m_worldModel.update();
		// Õ“Ë
		m_collisionUseCase->collisionAll(m_worldModel.getActors());

		m_worldModel.erase();
	}
	void World::draw() const
	{
		m_worldView.draw();
	}
}
