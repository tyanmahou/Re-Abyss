#include <abyss/components/Actor/Enemy/RollingTako/Builder.hpp>

#include <abyss/entities/Actor/Enemy/RollingTakoEntity.hpp>
#include <abyss/params/Actor/Enemy/RollingTako/Param.hpp>

#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/OutRoomChecker.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/RollingTako/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/RollingTako/State/RunState.hpp>


#include <abyss/views/Actor/Enemy/RollingTako/RollingTakoVM.hpp>

namespace
{
    class Presenter;
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
            .setAudioSettingGroupPath(U"Enemy/RollingTako/RollingTako.aase")
            .setVModelPresenter<Presenter>(pActor)
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

    class Presenter : public IVModelPresenter<RollingTakoVM>
    {
    private:
        RollingTakoVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setMotion(m_motion->get<Motion>())
                .setColorMul(m_colorCtrl->colorMul())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
        }
    public:
        Presenter(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<RollingTakoVM>())
        {}
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ColorCtrl> m_colorCtrl;
        Ref<MotionCtrl> m_motion;

        std::unique_ptr<RollingTakoVM> m_view;
    };
}

namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::RollingTako>;
    template<>
    void BuilderFromEntity<EnemyType::RollingTako>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        RollingTako::Builder::Build(pActor, static_cast<const RollingTakoEntity&>(entity));
    }
}
