#include "WorldPresenter.hpp"
#include <domain/usecase/CollisionUseCase.hpp>

void abyss::WorldPresenter::update()
{
	m_worldModel.update();
	// �Փ�
	m_collisionUseCase->collisionAll(m_worldModel.getActors());

	m_worldModel.erase();
}
