#include "State/PlayerSwimState.hpp"
#include "State/PlayerLadderState.hpp"
#include <abyss/views/Actors/Player/PlayerVM.hpp>

namespace abyss
{
    PlayerActor::PlayerActor() :
        m_state(this),
        m_view(std::make_shared<PlayerVM>())
    {
        this->tag = U"player";
        m_body
            .setSize({ 22, 80 })
            .setForward(Forward::Right)
            .setDeccelX(180)
            .setMaxSpeedX(240)
        ;

        m_state
            .add<PlayerSwimState>(State::Swim)
            .add<PlayerLadderState>(State::Ladder)
            .bind<BodyModel>(&PlayerActor::m_body)
            .bind<FootModel>(&PlayerActor::m_foot)
            .bind<ChargeModel>(&PlayerActor::m_charge)
        ;
    }

    void PlayerActor::update(double dt)
    {
        m_state.update(dt);
        //if (KeyD.down()) {
        //    m_body.setVelocity({ m_body.getForward() == Forward::Left ? 3.5 : -3.5,-3.5 });
        //}
        //if (KeyD.pressed()) {
        //    m_motion = Motion::Damge;
        //}
    }

    void PlayerActor::lastUpdate(double dt)
    {
        m_state.lastUpdate(dt);
    }

    void PlayerActor::setPos(const Vec2& pos)
    {
        m_body.setPos(pos);
    }

    const Vec2& PlayerActor::getPos() const
    {
        return m_body.getPos();
    }

    CShape PlayerActor::getCollider() const
    {
        return this->region();
    }

    void PlayerActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    RectF PlayerActor::region() const
    {
        return m_body.region();
    }
    void PlayerActor::accept(const ActVisitor& visitor)
    {
        visitor.visit(*this);
    }
    void PlayerActor::draw() const
    {
        m_state.draw();
    }
    PlayerVM* PlayerActor::getBindedView() const
    {
        return &m_view->setPos(m_body.getPos())
            .setVelocity(m_body.getVelocity())
            .setForward(m_body.getForward())
            .setCharge(m_charge.getCharge());
    }
    std::shared_ptr<PlayerActor> PlayerActor::Create()
    {
        return std::make_shared<PlayerActor>();
    }
}
