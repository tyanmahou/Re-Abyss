#include "State/BaseState.hpp"
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/params/Actors/CodeZero/Param.hpp>
#include <abyss/views/Actors/CodeZero/Head/HeadVM.hpp>

namespace abyss::CodeZero::Head
{
    HeadActor::HeadActor(CodeZeroActor* parent, HPModel* parentHp) :
        m_parent(parent),
        m_parentHp(parentHp),
        m_state(this),
        m_view(std::make_shared<HeadVM>())
    {
        this->layer = LayerGroup::Enemy;

        m_state.add<BaseState>(State::Base)
            .bind<CodeZeroActor*>(&HeadActor::m_parent)
            .bind<HPModel*>(&HeadActor::m_parentHp)
            .bind<Forward>(&HeadActor::m_forward)
            ;
    }
    s3d::Vec2 HeadActor::getPos() const
    {
        return m_parent->getPos() + Param::Head::Offset;
    }
    void HeadActor::update(double dt)
    {
        m_state.update(dt);
    }
    void HeadActor::draw() const
    {
        m_state.draw();
    }
    CShape HeadActor::getCollider() const
    {
        return s3d::Circle(this->getPos() + s3d::Vec2{0, 10}, Param::Head::ColRadius);
    }
    void HeadActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }
    bool HeadActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(static_cast<Receiver&>(*this))
            || visitor.visit(static_cast<IActor&>(*this));
    }
    HeadVM* HeadActor::getBindedView() const
    {
        return &m_view->setPos(this->getPos())
            .setForward(m_forward)
            .setIsDamaging(m_parentHp->isInInvincibleTime());
    }
}
