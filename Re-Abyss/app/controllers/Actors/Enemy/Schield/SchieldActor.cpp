#include <abyss/models/Actors/Enemy/Schield/State/WaitState.hpp>
#include <abyss/models/Actors/Enemy/Schield/State/AttackPlusState.hpp>
#include <abyss/models/Actors/Enemy/Schield/State/AttackCrossState.hpp>

#include <abyss/entities/Actors/Enemy/SchieldEntity.hpp>
#include <abyss/views/Actors/Enemy/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>

#include <abyss/models/Actors/Enemy/Schield/DamageModel.hpp>
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>
#include <abyss/types/CShape.hpp>
namespace abyss::Schield
{
    SchieldActor::SchieldActor(const SchieldEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_view(std::make_shared<SchieldVM>())
    {
        {
            m_hp->initHp(Param::Base::Hp);
        }
        {
            m_body->setSize(Param::Base::Size);
        }
        {
            (m_state = this->attach<StateModel<SchieldActor>>(this))
                ->add<WaitState>(State::Wait)
                .add<AttackPlusState>(State::AttackPlus)
                .add<AttackCrossState>(State::AttackCross)
                ;
        }
        this->attach<DamageModel>(this);
        this->attach<Enemy::DeadCallbackModel>(this);
    }
    s3d::Circle SchieldActor::getFaceCollider() const
    {
        s3d::Vec2 offset{ 53.0 * this->getForward(), 16};
        return s3d::Circle(this->getPos() + offset, Param::Wait::FaceColRadius);
    }
    CShape SchieldActor::getCollider() const
    {
        if (m_state->getState() == State::Wait) {
            s3d::Array<CShape> shapes;
            shapes << this->getFaceCollider() << m_body->region();
            return shapes;
        }
        return m_body->region();
    }
    bool SchieldActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }
    SchieldVM* SchieldActor::getBindedView() const
    {
        return &m_view->setPos(this->getPos())
            .setForward(this->getForward())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }
}
