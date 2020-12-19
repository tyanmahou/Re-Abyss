#include "CommonBuilder.hpp"

#include <abyss/models/Collision/LayerGroup.hpp>

#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/ReceiverData.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/DamageCtrl.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/BreathingCtrl.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>

#include <abyss/components/Actors/Enemy/DamageCallback.hpp>
#include <abyss/components/Actors/Enemy/DeadCallback.hpp>

namespace abyss::Actor::Enemy
{
    void CommonBuilder::Build(IActor* pActor, const BuildOption& opt)
    {
        // タグ
        pActor->setTag(Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{});

		// Body
		{
			pActor->attach<Body>(pActor)
				->initPos(opt.pos)
				.setForward(opt.forward)
				.setSize(opt.bodySize)
				.setPivot(opt.bodyPivot)
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
			pActor->attach<AttackerData>(1);
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