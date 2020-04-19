#include "State/CodeZeroHandPursuitState.hpp"
#include "State/CodeZeroHandAttakWaitState.hpp"
#include "State/CodeZeroHandAttackState.hpp"
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/views/Actors/CodeZero/Hand/CodeZeroHandVM.hpp>
#include <abyss/commons/LayerGroup.hpp>

namespace abyss
{
    CodeZeroHandActor::CodeZeroHandActor(CodeZeroActor* parent, Kind kind):
        m_parent(parent),
        m_kind(kind),
        m_state(this)
    {
        this->layer = LayerGroup::Enemy;

        auto forward = kind == Kind::Left ? Forward::Left : Forward::Right;
        m_view = std::make_shared<CodeZeroHandVM>(forward);

        s3d::Vec2 offsetPos{};
        m_body
            .setPos(parent->getPos() + s3d::Vec2{forward * -110, 90})
            .noneResistanced()
            ;
        m_state
            .add<CodeZeroHandPursuitState>(State::Pursuit)
            .add<CodeZeroHandAttackWaitState>(State::AttackWait)
            .add<CodeZeroHandAttackState>(State::Attack)
            .bind<BodyModel>(&CodeZeroHandActor::m_body)
            .bind<CodeZeroActor*>(&CodeZeroHandActor::m_parent)
            .bind<RotateModel>(&CodeZeroHandActor::m_rotate)
        ;
    }

    void CodeZeroHandActor::update(double dt)
    {
        m_state.update(dt);
    }

    void CodeZeroHandActor::draw() const
    {
        m_state.draw();
    }

    CShape CodeZeroHandActor::getCollider() const
    {
        return s3d::Circle(m_body.getPos(), CodeZeroParam::Hand::ColRadius);
    }

    bool CodeZeroHandActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(static_cast<Attacker&>(*this))
            || visitor.visit(static_cast<IActor&>(*this));
    }

    CodeZeroHandVM* CodeZeroHandActor::getBindedView() const
    {
        return &m_view
            ->setPos(m_body.getPos())
            .setRotate(m_rotate.getRotate());
    }

    void CodeZeroHandActor::changeState(State state)
    {
        m_state.changeState(state);
    }

    bool CodeZeroHandActor::tryAttack()
    {
        if (m_state.getState() == State::Pursuit) {
            m_state.changeState(State::AttackWait);
            return true;
        }
        return false;
    }

}
