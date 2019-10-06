#pragma once
#include <memory>
#include <domain/model/WorldModel.hpp>
namespace abyss
{
	class ICollisionUseCase;

	class WorldPresenter
	{
	private:
		WorldModel m_worldModel;
		std::unique_ptr<ICollisionUseCase> m_collisionUseCase;
	public:
		
		void update();
	};
}