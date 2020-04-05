#include "LaunSharkShotBaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/Common/EnemyDeadEffect.hpp>

namespace abyss
{
    void LaunSharkShotBaseState::destroy()
    {
        m_actor->getWorld()->addEffect<EnemyDeadEffect>(m_body->getPos());

        m_actor->destroy();
    }
    void LaunSharkShotBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
        m_hp = this->binded<HPModel>();
        m_rotate = this->binded<RotateModel>();
    }

    void LaunSharkShotBaseState::onCollisionStay(ICollider* col)
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
