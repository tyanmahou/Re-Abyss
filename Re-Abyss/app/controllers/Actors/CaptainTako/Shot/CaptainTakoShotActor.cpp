#include "State/CaptainTakoShotBaseState.hpp"
#include <abyss/views/Actors/CaptainTako/Shot/CaptainTakoShotVM.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/params/Actors/CaptainTako/CaptainTakoShotParam.hpp>

namespace abyss
{
    CaptainTakoShotActor::CaptainTakoShotActor(const s3d::Vec2& pos, Forward forward):
        m_state(this),
        m_view(std::make_shared<CaptainTakoShotVM>())
    {
        this->layer = LayerGroup::Enemy;

        m_state
            .add<CaptainTakoShotBaseState>(State::Base)
            .bind<BodyModel>(&CaptainTakoShotActor::m_body);

        m_body
            .setPos(pos)
            .setForward(forward)
            .noneResistanced()
            .setVelocityX(forward == Forward::Right ? CaptainTakoShotParam::Base::Speed : - CaptainTakoShotParam::Base::Speed)
            ;
        m_power = 1;
    }

    void CaptainTakoShotActor::start()
    {
    
    }

    void CaptainTakoShotActor::update(double dt)
    {
        m_state.update(dt);
    }

    CShape CaptainTakoShotActor::getCollider() const
    {
        return this->getColliderCircle();
    }

    void CaptainTakoShotActor::onCollisionStay(ICollider* col)
    {
        m_state.onCollisionStay(col);
    }

    s3d::Circle CaptainTakoShotActor::getColliderCircle() const
    {
        return s3d::Circle(m_body.getPos(), CaptainTakoShotParam::Base::ColRadius);
    }

    bool CaptainTakoShotActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(static_cast<Attacker&>(*this)) ||
            visitor.visit(static_cast<IActor&>(*this));
    }

    void CaptainTakoShotActor::draw() const
    {
        m_state.draw();
    }

    CaptainTakoShotVM* CaptainTakoShotActor::getBindedView() const
    {
        return &m_view
            ->setPos(m_body.getPos())
            .setForward(m_body.getForward());
    }

}
