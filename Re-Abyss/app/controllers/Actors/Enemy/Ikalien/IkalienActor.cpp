#include <abyss/models/Actors/Enemy/Ikalien/State/WaitState.hpp>
#include <abyss/models/Actors/Enemy/Ikalien/State/PursuitState.hpp>
#include <abyss/models/Actors/Enemy/Ikalien/State/SwimState.hpp>

#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/views/Actors/Enemy/Ikalien/IkalienVM.hpp>
#include <abyss/params/Actors/Enemy/Ikalien/Param.hpp>
#include <abyss/types/CShape.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
namespace abyss::Ikalien
{
    IkalienActor::IkalienActor(const IkalienEntity& entity):
        m_view(std::make_shared<IkalienVM>())
    {
        Enemy::EnemyBuilder builder(this);
        builder
            .setInitPos(entity.pos)
            .setBodyPivot(Param::Base::Pivot)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setColliderFunc([this] {
                return this->getCollider();
            })
            .setIsEnableMapCollider(false)
            .setAudioSettingGroupPath(U"Enemy/Ikalien/ikalien.aase")
            .build();

        {
            m_body->noneResistanced();
        }
        {
            m_rotate = this->attach<RotateModel>();
        }
        {
            this->attach<StateModel<IkalienActor>>(this)
                ->add<WaitState>(State::Wait)
                .add<PursuitState>(State::Pursuit)
                .add<SwimState>(State::Swim)
                ;
        }
    }
    CShape IkalienActor::getCollider() const
    {
        return s3d::Circle(m_body->getPivotPos(), Param::Base::ColRadius);
    }
    bool IkalienActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
    IkalienVM* IkalienActor::getBindedView() const
    {
        return &m_view->setTime(this->getDrawTimeSec())
            .setPos(this->getPos())
            .setVelocity(this->getVelocity())
            .setRotate(m_rotate->getRotate())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }
}
