#include <abyss/models/Actors/Enemy/Schield/State/WaitState.hpp>
#include <abyss/models/Actors/Enemy/Schield/State/AttackPlusState.hpp>
#include <abyss/models/Actors/Enemy/Schield/State/AttackCrossState.hpp>

#include <abyss/entities/Actors/Enemy/SchieldEntity.hpp>
#include <abyss/views/Actors/Enemy/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/models/Actors/Enemy/Schield/DamageModel.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace abyss::Schield
{
    SchieldActor::SchieldActor(const SchieldEntity& entity):
        m_view(std::make_shared<SchieldVM>())
    {
        Enemy::EnemyBuilder builder(this);

        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setInitHp(Param::Base::Hp)
            .setColliderFunc([this] {
                return this->getCollider();
            })
            .setAudioSettingGroupPath(U"Enemy/Schield/schield.aase")
            .setIsEnableDamage(false)
            .build();

        {
            (m_state = this->attach<OldStateModel<SchieldActor>>(this))
                ->add<WaitState>(State::Wait)
                .add<AttackPlusState>(State::AttackPlus)
                .add<AttackCrossState>(State::AttackCross)
                ;
        }
        this->attach<DamageModel>(this);
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
        return &m_view->setTime(this->getDrawTimeSec())
            .setPos(this->getPos())
            .setForward(this->getForward())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }
}
