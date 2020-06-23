#include "EnemyBuilder.hpp"
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>

#include <abyss/models/Collision/LayerGroup.hpp>

#include <abyss/models/Actors/Commons/DamageModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>
#include <abyss/models/Actors/Commons/BreathingModel.hpp>
#include <abyss/models/Actors/Commons/DeadCheackerModel.hpp>

#include <abyss/models/Actors/Enemy/DamageCallbackModel.hpp>
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>
namespace abyss::Enemy
{
	EnemyBuilder::EnemyBuilder(EnemyActor* pActor):
        m_pActor(pActor),
		m_pos(0, 0),
		m_bodySize(40, 40),
		m_bodyPivot(0, 0),
		m_forward(Forward::Left),
		m_initHp(1),
		m_colliderFunc([pActor]()->CShape {
			return pActor->region();
		}),
		m_audioSettingGroupPath(U"Enemy/enemy.aase")
    {
	
	}

    void EnemyBuilder::build() const
    {
		// Body
		{
			(m_pActor->m_body = m_pActor->attach<BodyModel>(m_pActor))
				->initPos(m_pos)
				.setForward(m_forward)
				.setSize(m_bodySize)
				.setPivot(m_bodyPivot)
			;
		}
		// HP
		{
			(m_pActor->m_hp = m_pActor->attach<HPModel>(m_pActor))
				->initHp(m_initHp)
				.setInvincibleTime(0.2);

		}

		// Collider
		if (m_isEnableCollider) {
			auto collider = m_pActor->attach<CustomColliderModel>(m_pActor);
			collider->setColFunc(m_colliderFunc);
			collider->setLayer(LayerGroup::Enemy);
		}
		// 地形Collider
		if (m_isEnableMapCollider) {
			auto mapCol = m_pActor->attach<MapColliderModel>(m_pActor);
			mapCol->setIsEnableRoomHit(m_isEnableRoomHit, m_isEnableRoomHitStrict);
		}
		// ダメージのコンポーネント
		if (m_isEnableDamage) {
			m_pActor->attach<DamageModel>(m_pActor);
		}
		{
			m_pActor->attach<DamageCallbackModel>(m_pActor);
		}
		if (m_isEnableDeadCallback) {
			m_pActor->attach<DeadCallbackModel>(m_pActor);
		}
		// 音源
		{
			m_pActor->attach<AudioSourceModel>(m_pActor)
				->load(m_audioSettingGroupPath);
		}
		// 呼吸
		if (m_isEnableBreathing) {
			m_pActor->attach<BreathingModel>(m_pActor);
		}

		// 死亡チェック
		{
			m_pActor->attach<DeadCheckerModel>(m_pActor)
				->setIsAutoDestroy(m_isAutoDestroy);
		}
    }
}
