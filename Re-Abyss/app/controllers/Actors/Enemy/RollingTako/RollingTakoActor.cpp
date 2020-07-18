#include "RollingTakoActor.hpp"

#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>
#include <abyss/models/Actors/Enemy/RollingTako/State/WaitState.hpp>
#include <abyss/models/Actors/Enemy/RollingTako/State/RunState.hpp>
#include <abyss/models/Actors/Enemy/RollingTako/DrawModel.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace abyss::RollingTako
{
    RollingTakoActor::RollingTakoActor(const RollingTakoEntity& entity):
        m_isWait(entity.wait)
    {
        Enemy::EnemyBuilder builder(this);

        if (m_isWait) {
            builder.setInitState<WaitState>();
        } else {
            builder.setInitState<RunState>();
        }
        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setBodyPivot(Param::Base::Pivot)
            .setInitHp(Param::Base::Hp)
            .setIsEnableRoomHit(true)
            .setAudioSettingGroupPath(U"Enemy/RollingTako/rolling_tako.aase")
            .build();

        {
            m_body->setMaxSpeedX(Param::Run::MaxSpeedX);
        }

        {
            this->attach<DrawModel>(this);
        }
    }

    bool RollingTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
}
