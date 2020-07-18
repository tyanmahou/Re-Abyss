#include <abyss/models/Actors/Enemy/Ikalien/State/WaitState.hpp>

#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/params/Actors/Enemy/Ikalien/Param.hpp>
#include <abyss/types/CShape.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
#include <abyss/models/Actors/Enemy/Ikalien/DrawModel.hpp>

namespace abyss::Ikalien
{
    IkalienActor::IkalienActor(const IkalienEntity& entity)
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
            .setInitState<WaitState>()
            .build();

        {
            m_body->noneResistanced();
        }
        {
            this->attach<RotateModel>();
        }
        {
            this->attach<DrawModel>(this);
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
}
