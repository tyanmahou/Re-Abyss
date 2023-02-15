#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    ParentCtrl::ParentCtrl(ActorObj* parent):
        m_parent(parent)
    {
    
    }
    void ParentCtrl::onStart()
    {
        m_body = m_parent->find<Actor::Body>();
        m_hp = m_parent->find<HP>();
        m_state = m_parent->find<StateCtrl>();
        m_parts = m_parent->find<PartsCtrl>();
    }
    Ref<HP> ParentCtrl::getHp() const
    {
        return m_hp;
    }
    const s3d::Vec2& ParentCtrl::getPos() const
    {
        return m_body->getPos();
    }
    bool ParentCtrl::isShotCharge() const
    {
        return m_parts->isShotCharge();
    }
    bool ParentCtrl::isExistParent() const
    {
        // コンポーネントが死んでるなら存在してない
        return m_hp.isValid();
    }
}
