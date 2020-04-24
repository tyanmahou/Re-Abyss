#include "State/WaitState.hpp"
#include "State/PursuitState.hpp"
#include "State/PursuitEndState.hpp"

#include <abyss/commons/LayerGroup.hpp>
#include <abyss/views/Actors/CodeZero/Shot/ShotVM.hpp>
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/ShotParam.hpp>
namespace abyss::CodeZero::Shot
{
    ShotActor::ShotActor(CodeZeroActor* parent):
        m_parent(parent),
        m_state(this),
        m_view(std::make_shared<ShotVM>())
    {
        this->layer = LayerGroup::Enemy;
        m_scale.set(0.0);
        m_body.setPos(parent->getPos()).noneResistanced();

        m_state
            .add<WaitState>(State::Wait)
            .add<PursuitState>(State::Pursuit)
            .add<PursuitEndState>(State::PursuitEnd)
            .bind<BodyModel>(&ShotActor::m_body)
            .bind<ScaleModel>(&ShotActor::m_scale)
            ;
    }

    void ShotActor::update(double dt)
    {
        m_state.update(dt);
    }

    void ShotActor::lastUpdate([[maybe_unused]] double dt)
    {
        m_state.lastUpdate(dt);
        if (m_parent->getHp().isDead()) {
            this->destroy();
        }
    }

    void ShotActor::draw() const
    {
        m_state.draw();
    }

    CShape ShotActor::getCollider() const
    {
        return s3d::Circle(m_body.getPos(), ShotParam::Base::ColRadius * m_scale.get());
    }
    bool ShotActor::accept(const ActVisitor& visitor)
    {
        bool success = visitor.visit(static_cast<Attacker&>(*this));
        success |= visitor.visit(static_cast<Receiver&>(*this));
        return success || visitor.visit(static_cast<IActor&>(*this));
    }

    ShotVM* ShotActor::getBindedView() const
    {
        return &m_view->setPos(m_body.getPos())
            .setScale(m_scale.get());
    }

}
