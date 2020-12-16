#include "RollingTakoActor.hpp"

#include <abyss/entities/Actors/Enemy/RollingTakoEntity.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>
#include <abyss/components/Actors/Enemy/RollingTako/State/WaitState.hpp>
#include <abyss/components/Actors/Enemy/RollingTako/State/RunState.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::RollingTako
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
            this->attach<ViewCtrl<RollingTakoVM>>()
                ->createBinder<ViewBinder>(this);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::RollingTako;

    class ViewBinder : public ViewCtrl<RollingTakoVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;

        std::unique_ptr<RollingTakoVM> m_view;
    private:
        RollingTakoVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<RollingTakoVM>())
        {}
    };
}
