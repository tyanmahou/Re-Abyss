//#include "HandActor.hpp"

#include <abyss/components/Actors/Enemy/CodeZero/Hand/State/PursuitState.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/State/AttakWaitState.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/State/AttackState.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/State/ShotChargeState.hpp>

#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/RotateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/HandCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Hand/KindCtrl.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>

#include <abyss/params/Actors/Enemy/CodeZero/HandParam.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Hand/HandVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    HandActor::HandActor(IActor* parent, Kind kind)
    {
        auto forward = kind == Kind::Left ? Forward::Left : Forward::Right;
        {
            this->attach<ParentCtrl>(parent);
        }
        {
            this->attach<KindCtrl>(kind);
        }
        {
            (m_state = this->attach<StateCtrl>(this))
                ->changeState<PursuitState>()
                ;
        }
        {
            auto col = this->attach<CustomCollider>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }
        {
            (m_body = this->attach<Body>(this))
                ->initPos(parent->find<Body>()->getPos() + s3d::Vec2{ forward * -110, 90 })
                .noneResistanced();
        }
        {
            m_rotate = this->attach<RotateCtrl>();
        }
        {
            m_hand = this->attach<HandCtrl>();
        }
        {
            this->attach<ViewCtrl<HandVM>>()
                ->createBinder<ViewBinder>(this, forward);
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

    bool HandActor::tryAttack()
    {
        if (m_state->isState<PursuitState>()) {
            m_state->changeState<AttackWaitState>();
            return true;
        }
        return false;
    }

    bool HandActor::tryPursuit()
    {
        if (m_state->isState<AttackState>() || m_state->isState<AttackWaitState>()) {
            return false;
        }
        m_state->changeState<PursuitState>();
        return true;
    }

    bool HandActor::tryShotCharge()
    {
        if (!m_state->isState<PursuitState>()) {
            return false;
        }
        m_state->changeState<ShotChargeState>();
        return true;
    }
    bool HandActor::isShotCharge() const
    {
        return m_state->isState<ShotChargeState>();
    }
    bool HandActor::isPursuit() const
    {
        return m_state->isState<PursuitState>();
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CodeZero;
    using namespace abyss::Actor::Enemy::CodeZero::Hand;

    class ViewBinder : public ViewCtrl<HandVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<RotateCtrl> m_rotate;
        std::unique_ptr<HandVM> m_view;
    private:
        HandVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setRotate(m_rotate->getRotate())
                ;
        }
        void setup() final
        {
            m_body = m_pActor->find<Body>();
            m_rotate = m_pActor->find<RotateCtrl>();
        }
    public:
        ViewBinder(IActor* pActor, Forward forward) :
            m_pActor(pActor),
            m_view(std::make_unique<HandVM>(forward))
        {}
    };
}