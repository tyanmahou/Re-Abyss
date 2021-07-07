#include "PhysicsManager.hpp"
#include "SimpleDetection.hpp"
#include <Siv3D.hpp>

namespace abyss::Physics
{
    PhysicsManager::PhysicsManager():
        m_detection(std::make_shared<SimpleDetection>())
    {}
    void PhysicsManager::addDetector(const std::shared_ptr<IDetector>&detector)
    {
        m_detectors.emplace_back(detector);
    }
    void PhysicsManager::addTerrain(const std::shared_ptr<ITerrain>&terrain)
    {
        m_terrains.emplace_back(terrain);
    }
    void PhysicsManager::onPhysicsCollision()
    {
        m_detection->collisionAll(m_detectors, m_terrains);
    }
    void PhysicsManager::cleanUp()
    {
        s3d::Erase_if(m_detectors, [](const Ref<IDetector>& d) {
            return !d;
        });
        s3d::Erase_if(m_terrains, [](const Ref<ITerrain>& d) {
            return !d;
        });
    }
}
