#include "CollisionModel.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>

namespace abyss::Slime::Sencer
{
    void CollisionModel::onCollisionStay(IActor* col)
    {
        col->accept([this](MapActor&) {
            m_onCollision = true;
        });
    }
}
