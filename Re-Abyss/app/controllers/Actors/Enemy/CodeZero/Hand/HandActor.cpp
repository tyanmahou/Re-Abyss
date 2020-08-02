#include "HandActor.hpp"

#include <abyss/models/Actors/Enemy/CodeZero/Hand/State/PursuitState.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Hand/State/AttakWaitState.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Hand/State/AttackState.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Hand/State/ShotChargeState.hpp>

#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Hand/HandModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Hand/KindModel.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>

#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/HandParam.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Hand/HandVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::CodeZero::Hand
{
    HandActor::HandActor(CodeZeroActor* parent, Kind kind)
    {
        auto forward = kind == Kind::Left ? Forward::Left : Forward::Right;
        {
            this->attach<ParentCtrlModel>(parent);
        }
        {
            this->attach<KindModel>(kind);
        }
        {
            (m_state = this->attach<StateModel>(this))
                ->changeState<PursuitState>()
                ;
        }
        {
            auto col = this->attach<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }
        {
            (m_body = this->attach<BodyModel>(this))
                ->initPos(parent->getPos() + s3d::Vec2{ forward * -110, 90 })
                .noneResistanced();
        }
        {
            m_rotate = this->attach<RotateModel>();
        }
        {
            m_hand = this->attach<HandModel>();
        }
        {
            this->attach<ViewModel<HandVM>>(forward)
                ->createBinder<ViewBinder>(this);
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
    using namespace abyss::CodeZero;
    using namespace abyss::CodeZero::Hand;

    class ViewBinder : public ViewModel<HandVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<RotateModel> m_rotate;
    private:
        HandVM* bind(HandVM* view) const
        {
            return &view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setRotate(m_rotate->getRotate())
                ;
        }
        void setup() override
        {
            m_body = m_pActor->find<BodyModel>();
            m_rotate = m_pActor->find<RotateModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor)
        {}
    };
}