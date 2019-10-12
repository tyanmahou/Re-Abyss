#include "WorldFacade.hpp"
#include <domain/usecase/CollisionUseCase.hpp>

namespace abyss
{
	WorldFacade::WorldFacade(std::unique_ptr<ICollisionUseCase>&& collision):
		m_collisionUseCase(std::move(collision))
	{
		m_worldView.setWorldModel(&m_worldModel);
	}
	void WorldFacade::update()
	{
		m_worldModel.update();
		// Õ“Ë
		m_collisionUseCase->collisionAll(m_worldModel.getActors());

		m_worldModel.erase();
	}
	void WorldFacade::draw() const
	{
		m_worldView.draw();
	}
}
