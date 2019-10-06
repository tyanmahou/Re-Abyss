#include "WorldPresenter.hpp"
#include <domain/usecase/CollisionUseCase.hpp>

void abyss::WorldPresenter::update()
{
	m_worldModel.update();
	// Õ“Ë
	m_collisionUseCase->collisionAll(m_worldModel.getObjects());

	m_worldModel.erase();
}
