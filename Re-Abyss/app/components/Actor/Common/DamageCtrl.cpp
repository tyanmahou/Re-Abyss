#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/IDamageCallback.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
	DamageCtrl::DamageCtrl(ActorObj* pActor):
		m_pActor(pActor),
		m_invincibleTime(1.0)
	{}
	DamageCtrl& DamageCtrl::setInvincibleTime(double invincibleTimeSec)
	{
		m_invincibleTime.reset(invincibleTimeSec);
		m_invincibleTime.toEnd();
		return *this;
	}
	bool DamageCtrl::isInInvincibleTime() const
	{
		return !m_invincibleTime.isEnd();
	}
	void DamageCtrl::onStart()
	{
		m_hp = m_pActor->find<HP>();
		m_colCtrl = m_pActor->find<ColCtrl>();
	}
	void DamageCtrl::onPostCollision()
	{
		double dt = m_pActor->deltaTime();
		m_invincibleTime.update(dt);
		m_comboHistory.update(dt);
		m_damageData = s3d::none;

		if (!m_isActive) {
			return;
		}
		if (m_pActor->isDestroyed()) {
			return;
		}
		if (this->isInInvincibleTime()) {
			// 無敵
			return;
		}

		DamageData data;
		const bool isDamaged = m_colCtrl->anyThen<Col::Attacker, 0>([this, &data](s3d::uint64 id, const Col::Attacker::Data& attacker) {
			const auto& record = m_comboHistory.find(id);
			if (!record.canDamage()) {
				return false;
			}
			s3d::int32 power = record.calcReductionPower(attacker.power, attacker.powerReductionRate);
			if (m_hp->damage(power)) {
				data.damage = power;
				data.pos = attacker.pos;
				data.velocity = attacker.velocity;

				// コンボ更新
				m_comboHistory.updateRecord(id, attacker.comboDuration, attacker.invincibleTime);
				return true;
			}
			return false;
		});
		if (isDamaged) {
			m_damageData = data;
			m_invincibleTime.reset();
			for (auto&& callback : m_pActor->finds<IDamageCallback>()) {
				callback->onDamaged(data);
			}
		}
	}

	void DamageCtrl::onStateStart()
	{
		m_isActive = true;
		m_isInvincibleState = false;
	}

}
