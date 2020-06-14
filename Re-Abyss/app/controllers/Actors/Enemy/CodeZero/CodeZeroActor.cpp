#include <abyss/models/Actors/Enemy/CodeZero/State/Phase1State.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/State/Phase2State.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/State/Phase3State.hpp>
#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Body/BodyVM.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>

#include <abyss/controllers/Actors/Enemy/CodeZero/Head/HeadActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace abyss::CodeZero
{
    CodeZeroActor::CodeZeroActor(const CodeZeroEntity& entity):
        m_view(std::make_shared<Body::BodyVM>())
    {
        Enemy::EnemyBuilder builder(this);
        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setIsEnableCollider(false)
            .setIsEnableBreathing(false)
            .build();
        {
            m_hp->initHp(Param::Base::Hp);
        }
        {
            m_body->noneResistanced();
        }
        {
            (m_state = this->attach<StateModel<CodeZeroActor>>(this))
                ->add<Phase1State>(State::Phase1)
                .add<Phase2State>(State::Phase2)
                .add<Phase3State>(State::Phase3)
                ;
        }
        {
            this->attach<PatternModel>(this);
        }
        m_order = -99;
    }

    void CodeZeroActor::start()
    {
        auto* const world = this->m_pManager->getModule<World>();
        m_head = world->create<Head::HeadActor>(this);
        m_leftHand = world->create<Hand::HandActor>(this, Hand::HandActor::Left);
        m_rightHand = world->create<Hand::HandActor>(this, Hand::HandActor::Right);
    }

    bool CodeZeroActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

    Body::BodyVM* CodeZeroActor::getBindedView() const
    {
        return &m_view->setPos(m_body->getPos());
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
