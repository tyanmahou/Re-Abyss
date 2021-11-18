#include "PhysicsManager.hpp"
#include "SimpleDetection.hpp"
#include <abyss/modules/Physics/base/IContacter.hpp>
#include <abyss/modules/Physics/base/ITerrain.hpp>
#include <Siv3D.hpp>

namespace abyss::Physics
{
    PhysicsManager::PhysicsManager():
        m_detection(std::make_shared<SimpleDetection>())
    {}
    void PhysicsManager::regist(const std::shared_ptr<IContacter>& contacter)
    {
        contacter->setId(m_idCounter.createId());
        m_contacters.push_back(contacter);
    }
    void PhysicsManager::regist(const std::shared_ptr<ITerrain>& terrain)
    {
        terrain->setId(m_idCounter.createId());
        m_terrains.emplace_back(terrain);
    }
    void PhysicsManager::onPhysicsCollision()
    {
        m_detection->collisionAll(m_contacters, m_terrains);
    }
    void PhysicsManager::cleanUp()
    {
        s3d::Erase_if(m_contacters, [this](const std::shared_ptr<IContacter>& c) {
            if (c->isDestroyed()) {
                return true;
            }
            return false;
        });
        s3d::Erase_if(m_terrains, [this](const std::shared_ptr<ITerrain>& t) {
            if (t->isDestroyed()) {
                return true;
            }
            return false;
        });
    }
}
