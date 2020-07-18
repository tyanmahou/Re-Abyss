#include "LaunSharkActor.hpp"

#include <abyss/models/Actors/Enemy/LaunShark/State/SwimState.hpp>
#include <abyss/entities/Actors/Enemy/LaunSharkEntity.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>

#include <abyss/models/Actors/Commons/TimeCounterModel.hpp>
#include <abyss/models/Actors/Enemy/LaunShark/DrawModel.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
namespace abyss::LaunShark
{
    LaunSharkActor::LaunSharkActor(const LaunSharkEntity& entity)
    {
        Enemy::EnemyBuilder builder(this);

        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setInitHp(Param::Base::Hp)
            .setIsEnableRoomHit(true, true)
            .setAudioSettingGroupPath(U"Enemy/LaunShark/laun_shark.aase")
            .setInitState<SwimState>()
            .build();

        {
            m_body
                ->noneResistanced();
        }
        {
            this->attach<TimeCounterModel>();
        }
        {
            this->attach<DrawModel>(this);
        }
    }
    
    bool LaunSharkActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }
}
