#include "BaseState.hpp"
#include <abyss/views/Actors/CodeZero/Head/HeadVM.hpp>
#include <abyss/commons/ActInclude.hpp>

#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/models/Actors/base/IDeadCallbackModel.hpp>

namespace abyss::CodeZero::Head
{
    void BaseState::setup()
    {
        auto parentCtrl = m_pActor->findComponent<ParentCtrlModel>();
        m_hp = parentCtrl->getHp().get();
        m_parent = parentCtrl->getParent();
        m_head = m_pActor->findComponent<HeadModel>().get();
    }
    void BaseState::update([[maybe_unused]]double dt)
    {
        auto playerPos = m_pActor->getModule<Player::PlayerActor>()->getPos();
        auto pos = m_head->getPos();

        if (m_parent->isShotCharge()) {
            m_head->setForward(Forward::None);
        }else if (playerPos.x > pos.x + 200) {
            m_head->setForward(Forward::Right);
        } else if (playerPos.x < pos.x - 200) {
            m_head->setForward(Forward::Left);
        } else {
            m_head->setForward(Forward::None);
        }
    }
    void BaseState::draw() const
    {
        this->m_pActor->getBindedView()->draw();
    }
    void BaseState::onCollisionStay(IActor* col)
    {
        col->accept([this](const Attacker& attacker) {
            if (m_hp->damage(attacker.getPower()) && m_hp->isDead()) {
                for (auto&& callback : m_parent->findComponents<IDeadCallbackModel>()) {
                    callback->onDead();
                }
            }
        });
    }
}
