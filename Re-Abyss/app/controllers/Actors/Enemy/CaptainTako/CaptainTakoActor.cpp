#include "CaptainTakoActor.hpp"

#include <abyss/entities/Actors/Enemy/CaptainTakoEntity.hpp>
#include <abyss/models/Actors/Enemy/CaptainTako/State/WaitState.hpp>
#include <abyss/models/Actors/Enemy/CaptainTako/DrawModel.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace abyss::CaptainTako
{
    CaptainTakoActor::CaptainTakoActor(const CaptainTakoEntity& entity)
    {
        Enemy::EnemyBuilder builder(this);
        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setBodyPivot(Param::Base::Pivot)
            .setInitHp(Param::Base::Hp)
            .setAudioSettingGroupPath(U"Enemy/CaptainTako/captain_tako.aase")
            .setInitState<WaitState>()
            .build();

        {
            this->attach<DrawModel>(this);
        }
    }
    bool CaptainTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
}
