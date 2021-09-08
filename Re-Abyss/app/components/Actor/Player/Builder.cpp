#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/params/Actor/Player/Param.hpp>

#include <abyss/components/Actor/Commons/AudioSource.hpp>
#include <abyss/components/Actor/Commons/BodyUpdater.hpp>
#include <abyss/components/Actor/Commons/BreathingCtrl.hpp>
#include <abyss/components/Actor/Commons/CustomCollider.hpp>
#include <abyss/components/Actor/Commons/DamageCtrl.hpp>
#include <abyss/components/Actor/Commons/MapCollider.hpp>
#include <abyss/components/Actor/Commons/FallChecker.hpp>
#include <abyss/components/Actor/Commons/DeadCheacker.hpp>
#include <abyss/components/Actor/Commons/CameraFixPos.hpp>
#include <abyss/components/Actor/Commons/LightCtrl.hpp>
#include <abyss/components/Actor/Commons/ReceiverData.hpp>

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
#include <abyss/views/Actor/Ooparts/base/OopartsView.hpp>
#include <abyss/views/Actor/Ooparts/base/ActDrawCallbackView.hpp>

namespace
{
	class Collider;
	class ViewBinder;
}
namespace abyss::Actor::Player
{
	void Builder::Build(ActorObj* pActor, const StartPosModel& startPos)
	{
		// 基本設定
        pActor->setDestoryTiming(DestoryTiming::Never);
		pActor->setTag(Tag::Player{});
        pActor->setOrder(10);

		// Body
		{
			pActor->attach<Body>(pActor)
				->initSize(Param::Base::Size)
                .initPos(startPos.getPos())
				.setForward(startPos.getForward())
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
				.setInvincibleTime(Param::Base::InvincibleTime);
		}
		// 衝突
		{
			pActor->attach<CollisionCtrl>(pActor)
				->setLayer(LayerGroup::Player);
			pActor->attach<CustomCollider>()
				->setImpl<Collider>(pActor);
		}
        // ReceiverData
        {
            pActor->attach<ReceiverData>();
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
            pActor->attach<DamageCtrl>(pActor);
            pActor->attach<DamageCallback>(pActor);
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
            pActor->attach<AudioSource>(pActor)
                ->load(U"Player/player.aase");
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
            pActor->attach<ViewCtrl<PlayerVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
        // Light
        {
            pActor->attach<LightCtrl>(pActor)
                ->setRadius(350.0);
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
    
    class Collider final : public CustomCollider::IImpl
    {
    public:
        Collider(ActorObj* pActor) :
            m_pActor(pActor)
        {}
        void onStart() override
        {
            m_body = m_pActor->find<Body>();
        }
        CShape getCollider() const override
        {
            return m_body->region();
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
    };

    class ViewBinder : public ViewCtrl<PlayerVM>::IBinder
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;
        Ref<ChargeCtrl> m_charge;
        Ref<AttackCtrl> m_attackCtrl;

        std::unique_ptr<PlayerVM> m_view;
    private:
        PlayerVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setVelocity(m_body->getVelocity())
                .setForward(m_body->getForward())
                .setCharge(m_charge->getCharge())
                .setIsAttacking(m_attackCtrl->isAttacking())
                .setIsDamaging(m_hp->isInInvincibleTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
            m_charge = m_pActor->find<ChargeCtrl>();
            m_attackCtrl = m_pActor->find<AttackCtrl>();

            auto oopartsView = std::make_unique<Ooparts::OopartsView>();
            oopartsView->setCallback(std::make_shared<Ooparts::ActDrawCallbackView>(m_pActor->getManager()));
            m_view->setOopartsView(std::move(oopartsView));
            m_view->setXtoAtkView(std::make_shared<XtoAtkVM>());
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<PlayerVM>())
        {}
    };
}
