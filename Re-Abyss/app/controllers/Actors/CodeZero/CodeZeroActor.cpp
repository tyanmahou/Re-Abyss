#include "State/CodeZeroBaseState.hpp"
#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>
#include <abyss/views/Actors/CodeZero/Body/CodeZeroBodyVM.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>

#include <abyss/controllers/Actors/CodeZero/Head/CodeZeroHeadActor.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/CodeZeroHandActor.hpp>
#include <abyss/controllers/World/World.hpp>

namespace abyss
{
    CodeZeroActor::CodeZeroActor(const CodeZeroEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_state(this),
        m_view(std::make_shared<CodeZeroBodyVM>())
    {
        m_state.add<CodeZeroBaseState>(State::Base);
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
        
    }

}
