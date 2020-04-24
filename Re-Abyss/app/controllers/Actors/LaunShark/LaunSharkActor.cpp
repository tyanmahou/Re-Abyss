#include "State/SwimState.hpp"
#include "State/AttackState.hpp"
#include "State/LauncherState.hpp"
#include <abyss/entities/Actors/Enemy/LaunSharkEntity.hpp>
#include <abyss/params/Actors/LaunShark/Param.hpp>
namespace abyss::LaunShark
{
    LaunSharkActor::LaunSharkActor(const LaunSharkEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_shared<LaunSharkVM>())
    {
        m_hp.setHp(Param::Base::Hp);
        m_body
            .noneResistanced()
            .setSize(Param::Base::Size);
        m_state
            .add<SwimState>(State::Swim)
            .add<LauncherState>(State::Launcher)
            .add<AttackState>(State::Attack)
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
