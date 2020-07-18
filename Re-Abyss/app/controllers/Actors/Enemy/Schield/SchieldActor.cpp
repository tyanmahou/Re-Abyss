#include "SchieldActor.hpp"

#include <abyss/models/Actors/Enemy/Schield/State/WaitState.hpp>

#include <abyss/entities/Actors/Enemy/SchieldEntity.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>
#include <abyss/models/Actors/Enemy/Schield/DamageModel.hpp>
#include <abyss/models/Actors/Enemy/Schield/FaceCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/Schield/DrawModel.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace abyss::Schield
{
    SchieldActor::SchieldActor(const SchieldEntity& entity)
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
            .setInitState<WaitState>()
            .build();
        {
            this->attach<DamageModel>(this);
        }
        {
            this->attach<DrawModel>(this);
        }
        {
            m_face = this->attach<FaceCtrlModel>(this);
        }
    }

    CShape SchieldActor::getCollider() const
    {
        if (m_face->isOnFace()) {
            s3d::Array<CShape> shapes;
            shapes << m_face->getCollider() << m_body->region();
            return shapes;
        }
        return m_body->region();
    }
    bool SchieldActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

}
