#include "BaseState.hpp"

namespace abyss::Ikalien
{
    void BaseState::setup()
    {
        m_body = this->binded<BodyModel>();
        m_rotate = this->binded<RotateModel>();
    }
    void BaseState::onCollisionStay(ICollider* col)
    {
        m_actor->EnemyActor::onCollisionStay(col);
    }
}
