#include "State/PursuitState.hpp"
#include "State/AttakWaitState.hpp"
#include "State/AttackState.hpp"
#include "State/ShotChargeState.hpp"
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/HandParam.hpp>
#include <abyss/views/Actors/CodeZero/Hand/HandVM.hpp>
#include <abyss/commons/LayerGroup.hpp>

namespace abyss::CodeZero::Hand
{
    HandActor::HandActor(CodeZeroActor* parent, Kind kind):
        m_parent(parent),
        m_kind(kind),
        m_state(this)
    {
        this->layer = LayerGroup::Enemy;

        auto forward = kind == Kind::Left ? Forward::Left : Forward::Right;
        m_view = std::make_shared<HandVM>(forward);

        s3d::Vec2 offsetPos{};
        m_body
            .setPos(parent->getPos() + s3d::Vec2{forward * -110, 90})
            .noneResistanced()
            ;
        m_state
            .add<PursuitState>(State::Pursuit)
            .add<AttackWaitState>(State::AttackWait)
            .add<AttackState>(State::Attack)
            .add<ShotChargeState>(State::ShotCharge)
            .bind<BodyModel>(&HandActor::m_body)
            .bind<CodeZeroActor*>(&HandActor::m_parent)
            .bind<RotateModel>(&HandActor::m_rotate)
            .bind<CodeZeroHandModel>(&HandActor::m_hand)
            ;
    }

    void HandActor::update(double dt)
    {
        m_state.update(dt);
    }

    void HandActor::draw() const
    {
        m_state.draw();
    }

    CShape HandActor::getCollider() const
    {
        return s3d::Circle(m_body.getPos(), HandParam::Base::ColRadius);
    }

    bool HandActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(static_cast<Attacker&>(*this))
            || visitor.visit(static_cast<IActor&>(*this));
    }

    HandVM* HandActor::getBindedView() const
    {
        return &m_view
            ->setPos(m_body.getPos())
            .setRotate(m_rotate.getRotate());
    }

    void HandActor::changeState(State state)
    {
        m_state.changeState(state);
    }

    bool HandActor::tryAttack()
    {
        if (m_state.getState() == State::Pursuit) {
            m_state.changeState(State::AttackWait);
            return true;
        }
        return false;
    }

    bool HandActor::tryPursuit()
    {
        if (m_state.getState() == State::Attack || m_state.getState() == State::AttackWait) {
            return false;
        }
        m_state.changeState(State::Pursuit);
        return true;
    }

    bool HandActor::tryShotCharge()
    {
        if (m_state.getState() != State::Pursuit) {
            return false;
        }
        m_state.changeState(State::ShotCharge);
        return true;
    }

}
