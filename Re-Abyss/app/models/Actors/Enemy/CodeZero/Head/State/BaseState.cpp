#include "BaseState.hpp"
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>

namespace abyss::CodeZero::Head
{
    void BaseState::setup()
    {
        auto parentCtrl = m_pActor->find<ParentCtrlModel>();
        m_hp = parentCtrl->getHp().get();
        m_parent = parentCtrl->getParent();
        m_head = m_pActor->find<HeadModel>().get();
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
}
