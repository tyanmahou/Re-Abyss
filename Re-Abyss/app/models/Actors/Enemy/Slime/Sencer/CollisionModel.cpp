#include "CollisionModel.hpp"
#include <abyss/commons/ActInclude.hpp>

namespace abyss::Slime::Sencer
{
    void CollisionModel::onCollisionStay(IActor* col)
    {
        col->accept([this](MapActor&) {
            m_onCollision = true;
        });
    }
}
