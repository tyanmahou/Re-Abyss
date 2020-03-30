#include "IkalienBaseState.hpp"

namespace abyss
{
    void IkalienBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
        m_ikalien = this->binded<IkalienModel>();
    }
    void IkalienBaseState::onCollisionStay(ICollider* col)
    {
        m_actor->EnemyActor::onCollisionStay(col);
    }
}
