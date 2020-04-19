#include "State/CodeZeroHeadBaseState.hpp"
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/views/Actors/CodeZero/Head/CodeZeroHeadVM.hpp>

namespace abyss
{
    CodeZeroHeadActor::CodeZeroHeadActor(CodeZeroActor* parent, HPModel* parentHp) :
        m_parent(parent),
        m_parentHp(parentHp),
        m_state(this),
        m_view(std::make_shared<CodeZeroHeadVM>())
    {
        this->layer = LayerGroup::Enemy;

        m_state.add<CodeZeroHeadBaseState>(State::Base)
            .bind<CodeZeroActor*>(&CodeZeroHeadActor::m_parent)
            .bind<HPModel*>(&CodeZeroHeadActor::m_parentHp)
            .bind<Forward>(&CodeZeroHeadActor::m_forward)
            ;
    }
    s3d::Vec2 CodeZeroHeadActor::getPos() const
    {
        return m_parent->getPos() + CodeZeroParam::Head::Offset;
    }
    void CodeZeroHeadActor::update(double dt)
    {
        m_state.update(dt);
    }
    void CodeZeroHeadActor::draw() const
    {
        m_state.draw();
    }
    CShape CodeZeroHeadActor::getCollider() const
    {
        return s3d::Circle(this->getPos() + s3d::Vec2{0, 10}, CodeZeroParam::Head::ColRadius);
    }
    void CodeZeroHeadActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    bool CodeZeroHeadActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(static_cast<Receiver&>(*this))
            || visitor.visit(static_cast<IActor&>(*this));
    }
    CodeZeroHeadVM* CodeZeroHeadActor::getBindedView() const
    {
        return &m_view->setPos(this->getPos())
            .setForward(m_forward)
            .setIsDamaging(m_parentHp->isInInvincibleTime());
    }
}
