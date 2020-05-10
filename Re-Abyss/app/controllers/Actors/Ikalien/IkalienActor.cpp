#include <abyss/models/Actors/Ikalien/State/WaitState.hpp>
#include <abyss/models/Actors/Ikalien/State/PursuitState.hpp>
#include <abyss/models/Actors/Ikalien/State/SwimState.hpp>

#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/views/Actors/Ikalien/IkalienVM.hpp>
#include <abyss/params/Actors/Ikalien/Param.hpp>

#include <abyss/models/Actors/Commons/DamageModel.hpp>
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

namespace abyss::Ikalien
{
    IkalienActor::IkalienActor(const IkalienEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_view(std::make_shared<IkalienVM>())
    {
        m_hp->setHp(Param::Base::Hp);
        m_body->noneResistanced().setPivot(Param::Base::Pivot);

        m_rotate = this->addComponent<RotateModel>();

        this->addComponent<exp::StateModel<IkalienActor>>(this)
            ->add<WaitState>(State::Wait)
            .add<PursuitState>(State::Pursuit)
            .add<SwimState>(State::Swim)
        ;
        this->addComponent<DamageModel>(this);
        this->addComponent<Enemy::DeadCallbackModel>(this);

        this->findComponent<CustomColliderModel>()->setColFunc([this] {
            return this->getCollider();
        });
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
        return &m_view->setPos(this->getPos())
            .setVelocity(this->getVelocity())
            .setRotate(m_rotate->getRotate())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }
}
