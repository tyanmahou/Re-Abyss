#include "World.hpp"
#include <abyss/models/Collision/CollisionModel.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>

namespace abyss
{
    World::World():
        m_collision(std::make_unique<SimpleCollision>())
    {}
    World::~World()
    {}
    void World::update()
    {
        m_actorsHolder.update();
        // 衝突
        m_collision->collisionAll(m_actorsHolder.getActors());

        m_actorsHolder.erase();
    }

    void World::reset()
    {
        m_actorsHolder.clear();
        m_collision->reset();
        if (m_pPlayer) {
            m_actorsHolder.pushActor(m_pPlayer);
        }
    }

    void World::draw() const
    {
        m_actorsHolder.draw();
        m_view.draw();
    }

    
}
