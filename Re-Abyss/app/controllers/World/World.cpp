#include "World.hpp"

#include <abyss/models/Collision/CollisionModel.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>

namespace abyss
{
    World::World():
        m_collision(std::make_unique<SimpleCollision>())
    {
    }
    World::~World()
    {}
    void World::setManager(Manager* pManager)
    {
        m_pManager = pManager;
    }
    void World::init()
    {
        this->flush();
    }
    void World::flush()
    {
        m_actorsHolder.flush();
    }
    void World::updateDeltaTime(double dt)
    {
        m_actorsHolder.updateDeltaTime(dt);
    }
    void World::update()
    {
        m_actorsHolder.update();
        // 衝突
        m_collision->collisionAll(this->finds<IColliderModel>());

        m_actorsHolder.lastUpdate();

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
