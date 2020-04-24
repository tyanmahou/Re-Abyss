#include "BaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/Common/EnemyDeadEffect.hpp>

namespace abyss::LaunShark::Shot
{
    void BaseState::destroy()
    {
        m_actor->getModule<World>()->addEffect<EnemyDeadEffect>(m_body->getPos());

        m_actor->destroy();
    }
    void BaseState::setup()
    {
        m_body = this->binded<BodyModel>();
        m_hp = this->binded<HPModel>();
        m_rotate = this->binded<RotateModel>();
    }

    void BaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const Receiver&) {
            // 当たって消える
            this->destroy();
        });
        col->accept([this](const Attacker& attacker) {
            if (m_hp->damage(attacker.getPower()) && m_hp->isDead()) {
                this->destroy();
            }
        });
    }

}
