#include "CodeZeroActor.hpp"

#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/State/Phase1State.hpp>

#include <abyss/controllers/Actors/Enemy/CodeZero/Head/HeadActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Body/BodyVM.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::CodeZero
{
    CodeZeroActor::CodeZeroActor(const CodeZeroEntity& entity)
    {
        Enemy::EnemyBuilder builder(this);
        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setIsEnableCollider(false)
            .setIsEnableMapCollider(false)
            .setIsEnableDamage(false)
            .setIsEnableDeadCallback(false)
            .setIsEnableBreathing(false)
            .setIsAutoDestroy(false)
            .build();
        {
            m_hp->initHp(Param::Base::Hp);
        }
        {
            m_body->noneResistanced();
        }
        {
            (m_state = this->attach<StateModel>(this))
                ->changeState<Phase1State>()
                ;
        }
        {
            this->attach<PatternModel>(this);
        }
        // view
        {
            this->attach<ViewModel<Body::BodyVM>>()
                ->createBinder<ViewBinder>(this);
        }
        m_order = -99;
    }

    void CodeZeroActor::start()
    {
        auto* const world = this->m_pManager->getModule<World>();
        m_head = world->create<Head::HeadActor>(this);
        m_leftHand = world->create<Hand::HandActor>(this, Hand::HandActor::Kind::Left);
        m_rightHand = world->create<Hand::HandActor>(this, Hand::HandActor::Kind::Right);
    }

    bool CodeZeroActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

    bool CodeZeroActor::isShotCharge() const
    {
        return m_leftHand->isShotCharge() || m_rightHand->isShotCharge();
    }

    void CodeZeroActor::setActiveAll(bool active)
    {
        this->setActive(active);
        m_head->setActive(active);
        m_leftHand->setActive(active);
        m_rightHand->setActive(active);
    }
}
namespace
{
    using namespace abyss;
    using namespace abyss::CodeZero;

    class ViewBinder : public ViewModel<Body::BodyVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
    private:
        Body::BodyVM* bind(Body::BodyVM* view) const
        {
            return &view->setPos(m_body->getPos());
        }
        void setup() override
        {
            m_body = m_pActor->find<BodyModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor)
        {}
    };
}