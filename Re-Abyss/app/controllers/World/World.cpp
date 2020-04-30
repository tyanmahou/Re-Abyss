#include "World.hpp"
#include "WorldTime.hpp"

#include <abyss/models/Collision/CollisionModel.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>

namespace abyss
{
    World::World():
        m_collision(std::make_unique<SimpleCollision>())
    {
    }
    World::~World()
    {}
    void World::setManager(ActManager* pManager)
    {
        m_pManager = pManager;
    }
    void World::init()
    {
        m_actorsHolder.init();
    }
    void World::update()
    {
        double dt = WorldTime::DeltaTime();

        m_actorsHolder.update(dt);
        // 衝突
        m_collision->collisionAll(m_actorsHolder.getActors());

        m_actorsHolder.lastUpdate(dt);

        m_actorsHolder.erase();
    }

    void World::reset()
    {
        m_actorsHolder.clear();
        m_collision->reset();
    }

    void World::draw() const
    {
        m_actorsHolder.draw();
        m_view.draw();
    }
}
