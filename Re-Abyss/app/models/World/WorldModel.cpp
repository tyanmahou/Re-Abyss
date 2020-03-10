#include "WorldModel.hpp"
#include <abyss/models/Collision/CollisionModel.hpp>
#include <abyss/models/actors/Player/PlayerActor.hpp>

namespace abyss
{
    WorldModel::WorldModel():
        m_collision(std::make_unique<SimpleCollision>())
    {}
    void WorldModel::update()
    {
        m_actorsModel.update();
        // 衝突
        m_collision->collisionAll(m_actorsModel.getActors());

        m_actorsModel.erase();
    }

    void WorldModel::reset()
    {
        m_actorsModel.clear();
        m_collision->reset();
        if (m_pPlayer) {
            m_actorsModel.pushActor(m_pPlayer);
        }
    }

    void WorldModel::draw() const
    {
        m_actorsModel.draw();
        m_view.draw();
    }

    
}
