#include "CollisionManager.hpp"
#include "SimpleDetection.hpp"
namespace abyss::Collision
{
	CollisionManager::CollisionManager():
		m_detection(std::make_shared<SimpleDetection>())
	{
	}
}

