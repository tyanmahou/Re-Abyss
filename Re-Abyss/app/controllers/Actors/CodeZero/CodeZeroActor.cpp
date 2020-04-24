#include "State/Phase1State.hpp"
#include "State/Phase2State.hpp"
#include "State/Phase3State.hpp"
#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>
#include <abyss/views/Actors/CodeZero/Body/BodyVM.hpp>
#include <abyss/params/Actors/CodeZero/Param.hpp>

#include <abyss/controllers/Actors/CodeZero/Head/HeadActor.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/HandActor.hpp>
#include <abyss/controllers/World/World.hpp>

#include <abyss/debugs/DebugLog/DebugLog.hpp>

namespace abyss::CodeZero
{
    CodeZeroActor::CodeZeroActor(const CodeZeroEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_shared<Body::BodyVM>())
    {
        m_state
            .add<Phase1State>(State::Phase1)
            .add<Phase2State>(State::Phase2)
            .add<Phase3State>(State::Phase3)
            .bind<HPModel>(&CodeZeroActor::m_hp)
            ;
        m_body.noneResistanced();
        m_hp.setHp(Param::Base::Hp);

        m_order = -99;
    }

    void CodeZeroActor::start()
    {
        auto* const world = this->m_pManager->getModule<World>();
        m_head = world->create<Head::HeadActor>(this, &m_hp);
        m_leftHand = world->create<Hand::HandActor>(this, Hand::HandActor::Left);
        m_rightHand = world->create<Hand::HandActor>(this, Hand::HandActor::Right);
    }

    void CodeZeroActor::update(double dt)
    {
        m_state.update(dt);
    }

    void CodeZeroActor::draw() const
    {
        m_state.draw();
        DebugLog::Print << U"HP: " << m_hp.value();
    }

    CShape CodeZeroActor::getCollider() const
    {
        return s3d::none;
    }

    bool CodeZeroActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

    Body::BodyVM* CodeZeroActor::getBindedView() const
    {
        return &m_view->setPos(m_body.getPos());
    }

    void CodeZeroActor::onDead()
    {
        // todo
        this->destroy();
        m_head->destroy();
        m_leftHand->destroy();
        m_rightHand->destroy();
    }

    bool CodeZeroActor::isShotCharge() const
    {
        return m_leftHand->isShotCharge() || m_rightHand->isShotCharge();
    }

}
