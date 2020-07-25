#include "RollingTakoActor.hpp"

#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>
#include <abyss/models/Actors/Enemy/RollingTako/State/WaitState.hpp>
#include <abyss/models/Actors/Enemy/RollingTako/State/RunState.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace
{
    class ViewBinder;
}
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
            this->attach<ViewModel<RollingTakoVM>>()
                ->createBinder<ViewBinder>(this);
        }
    }

    bool RollingTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::RollingTako;

    class ViewBinder : public ViewModel<RollingTakoVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;
    private:
        RollingTakoVM* bind(RollingTakoVM* view) const
        {
            return &view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime())
                ;
        }
        void setup() override
        {
            m_body = m_pActor->find<BodyModel>();
            m_hp = m_pActor->find<HPModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor)
        {}
    };
}
