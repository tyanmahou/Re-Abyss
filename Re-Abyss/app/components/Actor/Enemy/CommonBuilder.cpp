#include "CommonBuilder.hpp"

#include <abyss/components/Common/MotionCtrl.hpp>

#include <abyss/components/Actor/Common/AttackerData.hpp>
#include <abyss/components/Actor/Common/ReceiverData.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/CollisionCtrl.hpp>
#include <abyss/components/Actor/Common/CustomCollider.hpp>
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
        // タグ
        pActor->setTag(Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{});

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
				->initHp(opt.initHp)
				.setInvincibleTime(0.2);

		}
		// AttackerData
		{
			pActor->attach<AttackerData>(pActor, 1);
		}
		// ReceiverData
		{
			pActor->attach<ReceiverData>();
		}
		// Collider
		if (opt.isEnableCollider) {
			pActor->attach<CollisionCtrl>(pActor)
				->setLayer(LayerGroup::Enemy);

			auto collider = pActor->attach<CustomCollider>();
			if (opt.colliderImpl) {
				collider->setImpl(opt.colliderImpl);
			} else {
				auto colliderFunc = opt.colliderFunc ? opt.colliderFunc : [body = pActor->find<Body>()] ()->CShape{
					return body->region();
				};

				collider->setColFunc(colliderFunc);
			}
		}
		// 地形Collider
		if (opt.isEnableMapCollider) {
			pActor->attach<MapCollider>(pActor)
				->setIsEnableRoomHit(opt.isEnableRoomHit, opt.roomHitStrict);
		}
		// ダメージのコンポーネント
		if (opt.isEnableDamage) {
			pActor->attach<DamageCtrl>(pActor);
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