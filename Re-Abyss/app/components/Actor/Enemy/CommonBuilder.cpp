#include "CommonBuilder.hpp"

#include <abyss/components/Common/MotionCtrl.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>

#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/BodyCollider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Mover.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>

#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Actor/Common/BreathingCtrl.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>

#include <abyss/components/Actor/Enemy/ItemDropCtrl.hpp>
#include <abyss/components/Actor/Enemy/DamageCallback.hpp>
#include <abyss/components/Actor/Enemy/DeadCallback.hpp>

namespace abyss::Actor::Enemy
{
    void CommonBuilder::Build(ActorObj* pActor, const BuildOption& opt)
    {
		// Body
		{
			pActor->attach<Body>(pActor)
				->initPos(opt.pos)
				.setForward(opt.forward)
				.initSize(opt.bodySize)
				.initPivot(opt.bodyPivot)
				;

			pActor->attach<BodyUpdater>(pActor);
		}
		// HP
		{
			pActor->attach<HP>(pActor)
				->initHp(opt.initHp);

		}

		// 衝突
		if (opt.isEnableCollider) {
			// Collider設定
			auto collider = pActor->attach<Collider>();
			if (opt.collider) {
				collider->add(opt.collider);
			} else if(opt.colliderFunc){
				collider->add(opt.colliderFunc);
			} else {
				collider->add<Col::BodyCollider>(pActor);
			}
			// ColCtrl
			auto mainBranch = pActor->attach<ColCtrl>(pActor)
				->addBranch();

			mainBranch
				->addNode<Col::Node>(collider->main())
				.setLayer(ColSys::LayerGroup::Enemy)
				.attach<Col::Mover>(pActor)
				.attach<Col::Attacker>(pActor, 1)
				.attach<Col::Receiver>(pActor);
		}
		// 地形Collider
		if (opt.isEnableMapCollider) {
			pActor->attach<MapCollider>(pActor)
				->setIsEnableRoomHit(opt.isEnableRoomHit, opt.roomHitStrict);
		}
		// ダメージのコンポーネント
		if (opt.isEnableDamage) {
			pActor->attach<DamageCtrl>(pActor)
				->setInvincibleTime(0.2);
		}
		// ダメージコールバック
		{
			pActor->attach<DamageCallback>(pActor);
		}
		// 死亡時コールバック
		if (opt.isEnableDeadCallback) {
			pActor->attach<DeadCallback>(pActor);
		}
		// 音源
		{
			pActor->attach<AudioSource>(pActor)
				->load(opt.audioSettingGroupPath);
		}
		// 呼吸
		if (opt.isEnableBreathing) {
			pActor->attach<BreathingCtrl>(pActor);
		}
		if (opt.isEnableItemDrop) {
			pActor->attach<ItemDropCtrl>(pActor);
		}
		// 死亡チェック
		{
			pActor->attach<DeadChecker>(pActor)
				->setIsAutoDestroy(opt.isAutoDestroy);
		}

		// 状態管理
		{
			auto state = pActor->attach<StateCtrl>(pActor);
			if (opt.initState) {
				state->changeState(opt.initState);
			}
		}

		// View
		{
			pActor->attach<MotionCtrl>();
			auto vModel = pActor->attach<VModel>();
			if (opt.vModelBinder) {
				vModel->setBinder(opt.vModelBinder);
			}
		}
    }

    BuildOption::BuildOption():
        pos(0, 0),
        bodySize(40, 40),
        bodyPivot(0, 0),
        forward(Forward::Left),
        initHp(1),
        audioSettingGroupPath(U"Enemy/enemy.aase")
    {}
}