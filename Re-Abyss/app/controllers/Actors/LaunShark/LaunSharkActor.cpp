#include "State/LaunSharkSwimState.hpp"
#include "State/LaunSharkAttackState.hpp"
#include "State/LaunSharkLauncherState.hpp"
#include <abyss/entities/Enemy/LaunSharkEntity.hpp>

namespace abyss
{
    LaunSharkActor::LaunSharkActor(const LaunSharkEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_shared<LaunSharkVM>())
    {
        m_hp.setHp(10);
        m_body
            .noneResistanced()
            .setSize({120, 40});
        m_state
            .add<LaunSharkSwimState>(State::Swim)
            .add<LaunSharkLauncherState>(State::Launcher)
            .add<LaunSharkAttackState>(State::Attack)
            .bind<BodyModel>(&LaunSharkActor::m_body)
            .bind<TimeCounterModel>(&LaunSharkActor::m_timeCounter)
            ;
    }
    void LaunSharkActor::update(double dt)
    {
        m_state.update(dt);
    }
    void LaunSharkActor::lastUpdate(double dt)
    {
        m_state.lastUpdate(dt);
    }
    void LaunSharkActor::draw() const
    {
        m_state.draw();
    }
    void LaunSharkActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    bool LaunSharkActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }
    LaunSharkVM* LaunSharkActor::getBindedView() const
    {
        return &m_view->setPos(m_body.getPos())
            .setForward(m_body.getForward())
            .setIsDamaging(m_hp.isInInvincibleTime());
    }
}
