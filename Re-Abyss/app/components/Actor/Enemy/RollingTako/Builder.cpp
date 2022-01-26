#include <abyss/components/Actor/Enemy/RollingTako/Builder.hpp>

#include <abyss/entities/Actor/Enemy/RollingTakoEntity.hpp>
#include <abyss/params/Actor/Enemy/RollingTako/Param.hpp>

#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/OutRoomChecker.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/RollingTako/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/RollingTako/State/RunState.hpp>


#include <abyss/views/Actor/Enemy/RollingTako/RollingTakoVM.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::RollingTako
{
    void Builder::Build(ActorObj* pActor, const RollingTakoEntity& entity)
    {
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setBodyPivot(Param::Base::Pivot)
            .setInitHp(Param::Base::Hp)
            .setIsEnableRoomHit(true)
            .setAudioSettingGroupPath(U"Enemy/RollingTako/rolling_tako.aase")
            .setVModelBinder<ViewBinder>(pActor)
        );

        // 初期状態
        {
            auto stateCtrl = pActor->find<StateCtrl>();
            if (entity.wait) {
                stateCtrl->changeState<WaitState>();
            } else {
                stateCtrl->changeState<RunState>();
            }
        }

        // Body調整
        {
            pActor->find<Body>()->setMaxSpeedX(Param::Run::MaxSpeedX);
        }
        // ルーム外死亡
        {
            pActor->attach<OutRoomChecker>(pActor);
        }
        // 描画
        {
            pActor->find<MotionCtrl>()
                ->set(entity.wait ? Motion::Wait : Motion::Run);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::RollingTako;

    class ViewBinder : public IVModelBinder<RollingTakoVM>
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<DamageCtrl> m_damage;
        Ref<MotionCtrl> m_motion;

        std::unique_ptr<RollingTakoVM> m_view;
    private:
        RollingTakoVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_damage->isInInvincibleTime())
                .setMotion(m_motion->get<Motion>())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_damage = m_pActor->find<DamageCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<RollingTakoVM>())
        {}
    };
}
