#include "IkalienBaseState.hpp"

namespace abyss
{
    void IkalienBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
        m_rotate = this->binded<RotateModel>();
    }
    void IkalienBaseState::onCollisionStay(ICollider* col)
    {
        m_actor->EnemyActor::onCollisionStay(col);
    }
}
