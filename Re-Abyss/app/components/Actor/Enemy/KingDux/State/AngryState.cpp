#include <abyss/components/Actor/Enemy/KingDux/State/AngryState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Common/ColorAnim/InvincibleColor.hpp>
#include <abyss/components/Effect/Misc/ShockWaveDist/Builder.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void AngryState::start()
	{
		m_eyeCtrl->setAngryMode();
		m_damageCtrl->setInvincibleState(true);
		m_pActor->find<ColorAnim::InvincibleColor>()->startAnim(2.0);
		m_motion->set(Motion::Angry);
		m_motion->setAnimeTime(0.0);

		// 画面フラッシュ
		m_pActor->getModule<SpecialEffects>()->flush()->start(0, 0.5);
	}
	void AngryState::end()
	{
		if (m_quake) {
			m_quake->stop();
		}
		m_pActor->find<ColorAnim::InvincibleColor>()->endAnim();

		m_motion->set(Motion::Wait);
		m_motion->setAnimeTime(0.0);
	}
	Coro::Fiber<> AngryState::updateAsync()
	{
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.3);
		m_phase = Phase::Open;
		m_animTimer.reset(0.7);
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.7);

		m_phase = Phase::Wait;
		m_quake = m_pActor->getModule<Camera>()->startQuake(Param::Shout::QuakeOffset);

		const double& timeSec = Param::Shout::Time;

		for ([[maybe_unused]]int32 count : s3d::step(Param::Shout::Count)) {
			m_pActor->getModule<Effects>()->createWorldFront<Effect::Misc::ShockWaveDist::Builder>(
				m_body->getPos() + Vec2{0, 200},
				Param::Shout::Radius,
				Param::Shout::Power,
				timeSec
				);
			co_await BehaviorUtil::WaitForSeconds(m_pActor, Param::Shout::WaitTime);
		}
		m_quake->stop();

		m_phase = Phase::Close;
		m_animTimer.reset(0.5);
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.0);

		this->changeState<WaitState>();
		co_return;
	}
	void AngryState::update()
	{
		const auto dt = m_pActor->deltaTime();
		switch (m_phase) {
		case Phase::Open:
			m_animTimer.update(dt);
			m_motion->setAnimeTime(s3d::EaseInQuint(m_animTimer.rate()));
			break;
		case Phase::Close:
			m_animTimer.update(dt);
			m_motion->setAnimeTime(s3d::EaseInQuint(m_animTimer.invRate()));
			break;
		default:
			break;
		}
	}
}
