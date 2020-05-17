#include <abyss/models/Actors/Enemy/CodeZero/Hand/State/PursuitState.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Hand/State/AttakWaitState.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Hand/State/AttackState.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Hand/State/ShotChargeState.hpp>

#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/HandParam.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Hand/HandVM.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>

namespace abyss::CodeZero::Hand
{
    HandActor::HandActor(CodeZeroActor* parent, Kind kind):
        m_kind(kind)
    {
        auto forward = kind == Kind::Left ? Forward::Left : Forward::Right;
        m_view = std::make_shared<HandVM>(forward);

        {
            this->attach<ParentCtrlModel>(parent);
        }
        {
            (m_state = this->attach<StateModel<HandActor>>(this))
                ->add<PursuitState>(State::Pursuit)
                .add<AttackWaitState>(State::AttackWait)
                .add<AttackState>(State::Attack)
                .add<ShotChargeState>(State::ShotCharge)
                ;
        }
        {
            auto col = this->attach<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }
        {
            (m_body = this->attach<BodyModel>())
                ->initPos(parent->getPos() + s3d::Vec2{ forward * -110, 90 })
                .noneResistanced();
        }
        {
            m_rotate = this->attach<RotateModel>();
        }
        {
            m_hand = this->attach<HandModel>();
        }
    }

    CShape HandActor::getCollider() const
    {
        return s3d::Circle(m_body->getPos(), HandParam::Base::ColRadius);
    }

    bool HandActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(static_cast<Attacker&>(*this))
            || visitor.visit(static_cast<IActor&>(*this));
    }

    HandVM* HandActor::getBindedView() const
    {
        return &m_view
            ->setPos(m_body->getPos())
            .setRotate(m_rotate->getRotate());
    }

    void HandActor::changeState(State state)
    {
        m_state->changeState(state);
    }

    bool HandActor::tryAttack()
    {
        if (m_state->getState() == State::Pursuit) {
            m_state->changeState(State::AttackWait);
            return true;
        }
        return false;
    }

    bool HandActor::tryPursuit()
    {
        if (m_state->getState() == State::Attack || m_state->getState() == State::AttackWait) {
            return false;
        }
        m_state->changeState(State::Pursuit);
        return true;
    }

    bool HandActor::tryShotCharge()
    {
        if (m_state->getState() != State::Pursuit) {
            return false;
        }
        m_state->changeState(State::ShotCharge);
        return true;
    }
    bool HandActor::isShotCharge() const
    {
        return m_state->getState() == State::ShotCharge;
    }
    bool HandActor::isPursuit() const
    {
        return m_state->getState() == State::Pursuit;
    }
}
