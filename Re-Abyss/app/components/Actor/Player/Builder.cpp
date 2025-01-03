﻿#include <abyss/components/Actor/Player/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/params/Actor/Player/Param.hpp>

#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/BreathingCtrl.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/ColorAnim/DamageColor.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Actor/Common/FallChecker.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Common/CameraFixPos.hpp>
#include <abyss/components/Actor/Common/LightCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/BossFadeMask.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/BodyCollider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Mover.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>

#include <abyss/components/Actor/Player/AttackCtrl.hpp>
#include <abyss/components/Actor/Player/OopartsCtrl.hpp>
#include <abyss/components/Actor/Player/RestartCtrl.hpp>
#include <abyss/components/Actor/Player/RoomMoveChecker.hpp>
#include <abyss/components/Actor/Player/UICtrl.hpp>
#include <abyss/components/Actor/Player/DebugCtrl.hpp>
#include <abyss/components/Actor/Player/GimmickReactCtrl.hpp>
#include <abyss/components/Actor/Player/DamageCallback.hpp>
#include <abyss/components/Actor/Player/ForwardCtrl.hpp>
#include <abyss/components/Actor/Player/MoveSwim.hpp>
#include <abyss/components/Actor/Player/State/SwimState.hpp>
#include <abyss/components/Actor/Player/CameraTarget.hpp>

#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <abyss/views/Actor/Player/MotionUtil.hpp>
#include <abyss/views/Actor/Player/ChargeEffectVM.hpp>
#include <abyss/views/Actor/Ooparts/base/OopartsView.hpp>

namespace
{
	class Presenter;
}
namespace abyss::Actor::Player
{
	void Builder::Build(
        ActorObj* pActor,
        const PlayerDesc& desc
    ) {
		// 基本設定
        pActor->setDestoryTiming(DestoryTiming::Never);

        Vec2 initPos{0, 0};
        Forward forward = Forward::Right();
        if (desc.direct) {
            initPos = desc.direct->pos;
            forward = desc.direct->forward;
        } else {
            auto startPos = pActor->getModule<Stage>()->findStartPos(desc.startId);
            initPos = startPos->getPos();
            forward = startPos->getForward();
        }

		// Body
		{
			pActor->attach<Body>(pActor)
				->initSize(Param::Base::Size)
                .initPos(initPos)
                .setAnchor(BodyAnchor::BottomCenter)
				.setForward(forward)
				;
            pActor->attach<BodyUpdater>(pActor);

            // 移動制御
            pActor->attach<ForwardCtrl>(pActor);
            pActor->attach<MoveSwim>(pActor);
		}
		// Foot
		{
			pActor->attach<Foot>();
		}
		// HP
		{
            pActor->attach<HP>(pActor)
                ->initHp(Param::Base::Hp)
                .setHp(desc.hp)
                ;
		}
		// 衝突
		{
            auto collider = pActor->attach<Collider>();
            collider->add<Col::BodyCollider>(pActor);

            pActor->attach<ColCtrl>(pActor)
                ->addBranch()
                ->addNode<Col::Node>(collider->main())
                .setLayer(ColSys::LayerGroup::Player)
                .attach<Col::Mover>(pActor)
                .attach<Col::Receiver>(pActor)
                ;
		}
		// 地形判定
		{
            pActor->attach<MapCollider>(pActor)
                ->setIsEnableTrajectory(true) // 移動差分考慮する
                ;
		}
        // カメラターゲット
        {
            pActor->attach<CameraTarget>(pActor);
        }
        // カメラによる座標調整
        {
            pActor->attach<CameraFixPos>(pActor);
        }
        // ダメージ制御
        {
            pActor->attach<DamageCtrl>(pActor)
                ->setInvincibleTime(Param::Base::InvincibleTime);
            pActor->attach<DamageCallback>(pActor);

            pActor->attach<ColorCtrl>(pActor);
            pActor->attach<ColorAnim::DamageColor>(pActor);
        }
        // 部屋移動の検知
        {
            pActor->attach<RoomMoveChecker>(pActor);
        }
        // 死亡チェック
        {
            pActor->attach<DeadChecker>(pActor)
                ->setIsAutoDestroy(false);

            // 落下死
            pActor->attach<FallChecker>(pActor);

            // リスタート
            pActor->attach<RestartCtrl>(pActor);
        }
        // AudioSource
        {
            pActor->attach<AudioSource>(pActor);
        }
        // State
        {
            pActor->attach<StateCtrl>(pActor)
                ->changeState<SwimState>()
                ;

            pActor->attach<StateChecker>(pActor);
        }
        // ギミック反応
        {
            pActor->attach<GimmickReactCtrl>(pActor);
        }
        // AttackCtrl
        {
            pActor->attach<AttackCtrl>(pActor);
        }
		// Charge
		{
			pActor->attach<ChargeCtrl>();
		}
        // オーパーツ制御
        {
            pActor->attach<OopartsCtrl>(pActor);
        }
        // 呼吸
        {
            pActor->attach<BreathingCtrl>(pActor)
                ->setOffset(s3d::Vec2{ 0, -20 });
        }
        // View
        {
            pActor->attach<MotionCtrl>();
            pActor->attach<VModel>()
                ->setPresenter<Presenter>(pActor)
                .setOrder(DrawOrder::World::Player);
        }
        // Light
        {
            pActor->attach<LightCtrl>(pActor)
                ->setRadius(350.0)
                .setOrder(DrawOrder::World::Player);
        }
        // BossFadeMask
        {
            pActor->attach<BossFadeMask>(pActor)
                ->setDrawer<BossFadeMaskFromMainVModel>(pActor)
                ;
        }
        // UI制御
        {
            pActor->attach<UICtrl>(pActor);
        }
#if ABYSS_DEBUG
        // デバッグ制御
        {
            pActor->attach<DebugCtrl>(pActor);
        }
#endif
	}
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Player;

    class Presenter final : public IVModelPresenterBase
    {
    public:
        Presenter(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<PlayerVM>()),
            m_oopartsView(std::make_unique<Ooparts::OopartsView>()),
            m_chargeView(std::make_unique<ChargeEffectVM>())
        {}
    public:
        void onStart() override
        {
            m_body = m_pActor->find<Body>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
            m_charge = m_pActor->find<ChargeCtrl>();
            m_attackCtrl = m_pActor->find<AttackCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
        }

        void onDraw() const override
        {
            auto* player = this->bind();
            if (m_attackCtrl->isAttacking()) {
                if (auto handOffsetPos = MotionUtil::AtkHandPos(player)) {
                    // 攻撃中の描画上書き
                    auto ooparts = this->bindOoparts(*handOffsetPos);

                    ooparts->setPipeline(Ooparts::OopartsView::Pipeline::Back).draw();
                    player->draw();
                    ooparts->setPipeline(Ooparts::OopartsView::Pipeline::Front).draw();
                    return;
                }
            }
            player->draw();
            bindChargeEft()->draw();
        }
    private:
        PlayerVM* bind() const
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setVelocity(m_body->getVelocity())
                .setForward(m_body->getForward())
                .setIsAttacking(m_attackCtrl->isAttacking())
                .setMotion(m_motion->get<Motion>())
                .setAnimeTime(m_motion->animeTime())
                .setColorMul(m_colorCtrl->colorMul())
                ;
        }
        Ooparts::OopartsView* bindOoparts(const s3d::Vec2& handOffset) const
        {
            return &m_oopartsView
                ->setTime(m_pActor->getTimeSec())
                .setForward(m_body->getForward())
                .setPos(m_body->getCenterPos() + handOffset)
                ;
        }
        ChargeEffectVM* bindChargeEft()const
        {
            return &m_chargeView
                ->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getCenterPos())
                .setCharge(m_charge->getCharge())
                ;
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ColorCtrl> m_colorCtrl;
        Ref<ChargeCtrl> m_charge;
        Ref<AttackCtrl> m_attackCtrl;
        Ref<MotionCtrl> m_motion;

        std::unique_ptr<PlayerVM> m_view;
        std::unique_ptr<Ooparts::OopartsView> m_oopartsView;
        std::unique_ptr<ChargeEffectVM> m_chargeView;
    };
}
