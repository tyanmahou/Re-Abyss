#include "State/CodeZeroPhase1State.hpp"
#include "State/CodeZeroPhase2State.hpp"
#include "State/CodeZeroPhase3State.hpp"
#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>
#include <abyss/views/Actors/CodeZero/Body/CodeZeroBodyVM.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>

#include <abyss/controllers/Actors/CodeZero/Head/CodeZeroHeadActor.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/CodeZeroHandActor.hpp>
#include <abyss/controllers/World/World.hpp>

#include <abyss/debugs/DebugLog/DebugLog.hpp>

namespace abyss
{
    CodeZeroActor::CodeZeroActor(const CodeZeroEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_shared<CodeZeroBodyVM>())
    {
        m_state
            .add<CodeZeroPhase1State>(State::Phase1)
            .add<CodeZeroPhase2State>(State::Phase2)
            .add<CodeZeroPhase3State>(State::Phase3)
            .bind<HPModel>(&CodeZeroActor::m_hp)
            ;
        m_body.noneResistanced();
        m_hp.setHp(CodeZeroParam::Base::Hp);

        m_order = -99;
    }

    void CodeZeroActor::start()
    {
        auto* const world = this->m_pManager->getModule<World>();
        m_head = world->create<CodeZeroHeadActor>(this, &m_hp);
        m_leftHand = world->create<CodeZeroHandActor>(this, CodeZeroHandActor::Left);
        m_rightHand = world->create<CodeZeroHandActor>(this, CodeZeroHandActor::Right);
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

    CodeZeroBodyVM* CodeZeroActor::getBindedView() const
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

}
