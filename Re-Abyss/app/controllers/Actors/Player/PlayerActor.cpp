#include "State/PlayerSwimState.hpp"
#include "State/PlayerLadderState.hpp"
#include "State/PlayerDamageState.hpp"
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/params/Actors/Player/PlayerParam.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>

namespace abyss
{
    PlayerActor::PlayerActor() :
        m_state(this),
        m_view(std::make_shared<PlayerVM>())
    {
        this->m_isDontDestoryOnLoad = true;

        this->tag = U"player";
        this->layer = LayerGroup::Player;
        m_body
            .setSize(PlayerParam::Base::Size)
            .setForward(Forward::Right)
        ;

        m_state
            .add<PlayerSwimState>(State::Swim)
            .add<PlayerLadderState>(State::Ladder)
            .add<PlayerDamageState>(State::Damage)
            .bind<BodyModel>(&PlayerActor::m_body)
            .bind<FootModel>(&PlayerActor::m_foot)
            .bind<ChargeModel>(&PlayerActor::m_charge)
            .bind<HPModel>(&PlayerActor::m_hp)
            ;
        m_hp
            .setHp(PlayerParam::Base::Hp)
            .setInvincibleTime(PlayerParam::Base::InvincibleTime);
    }
    void PlayerActor::start()
    {
        m_pManager->set(this);
    }
    void PlayerActor::update(double dt)
    {
        m_state.update(dt);
    }

    void PlayerActor::lastUpdate(double dt)
    {
        m_state.lastUpdate(dt);
    }

    void PlayerActor::setPos(const Vec2& pos)
    {
        m_body.setPos(pos);
    }

    void PlayerActor::setForward(const Forward& forward)
    {
        m_body.setForward(forward);
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
    bool PlayerActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
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
            .setCharge(m_charge.getCharge())
            .setIsDamaging(m_hp.isInInvincibleTime())
            .setManager(m_pManager)
            ;
    }
    std::shared_ptr<PlayerActor> PlayerActor::Create()
    {
        return std::make_shared<PlayerActor>();
    }
}
