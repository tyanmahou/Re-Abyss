#include "State/CodeZeroBaseState.hpp"
#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>
#include <abyss/views/Actors/CodeZero/Body/CodeZeroBodyVM.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>

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

}
