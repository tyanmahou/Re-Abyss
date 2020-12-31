#include "Builder.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/params/Actors/Player/Param.hpp>

#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/BreathingCtrl.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/FallChecker.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Commons/CameraFixPos.hpp>
#include <abyss/components/Actors/Commons/LightCtrl.hpp>
#include <abyss/components/Actors/Commons/ReceiverData.hpp>

#include <abyss/components/Actors/Player/PlayerProxy.hpp>
#include <abyss/components/Actors/Player/AttackCtrl.hpp>
#include <abyss/components/Actors/Player/OopartsCtrl.hpp>
#include <abyss/components/Actors/Player/RestartCtrl.hpp>
#include <abyss/components/Actors/Player/RoomMoveChecker.hpp>
#include <abyss/components/Actors/Player/UICtrl.hpp>
#include <abyss/components/Actors/Player/DebugCtrl.hpp>
#include <abyss/components/Actors/Player/GimmickReactCtrl.hpp>
#include <abyss/components/Actors/Player/State/SwimState.hpp>

#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/views/Actors/Ooparts/base/ActDrawCallbackView.hpp>

namespace
{
	class Collider;
	class ViewBinder;
}
namespace abyss::Actor::Player
{
	void Builder::Build(IActor* pActor, const StartPosModel& startPos)
	{
		// 基本設定
		pActor->setIsDontDestoryOnLoad();
		pActor->setTag(Tag::Player{});
        pActor->setOrder(10);

		// Body
		{
			pActor->attach<Body>(pActor)
				->setSize(Param::Base::Size)
                .initPos(startPos.getPos())
				.setForward(startPos.getForward())
				;
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
			pActor->attach<MapCollider>(pActor);
		}
        // カメラによる座標調整
        {
            pActor->attach<CameraFixPos>(pActor);
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
                ->setRadius(700.0);
        }
        // UI制御
        {
            pActor->attach<UICtrl>(pActor);
        }
        // プロキシ
        {
            pActor->attach<PlayerProxy>(pActor);
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
        Collider(IActor* pActor) :
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
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
    };

    class ViewBinder : public ViewCtrl<PlayerVM>::IBinder
    {
        IActor* m_pActor = nullptr;
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
                .setManager(m_pActor->getManager())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
            m_charge = m_pActor->find<ChargeCtrl>();
            m_attackCtrl = m_pActor->find<AttackCtrl>();

            auto xtoView = std::make_unique<XtoAtkVM>();
            xtoView->setCallback(std::make_unique<Ooparts::ActDrawCallbackView>(xtoView.get(), m_pActor->getManager()));
            m_view->setXtoAtkView(std::move(xtoView));
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<PlayerVM>())
        {}
    };
}
