#include <abyss/components/Actor/Enemy/KingDux/State/AngryState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Effect/Misc/ShockWaveDist/Builder.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void AngryState::start()
	{
	}
	void AngryState::end()
	{
		if (m_quake) {
			m_quake->stop();
		}
	}
	Coro::Task<> AngryState::task()
	{
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.0);

		m_quake = m_pActor->getModule<Camera>()->startQuake();

		const double& timeSec = Param::Shout::Time;

		for ([[maybe_unused]]int32 count : s3d::step(Param::Shout::Count)) {
			m_pActor->getModule<Effects>()->createWorldFront<Effect::Misc::ShockWaveDist::Builder>(
				m_body->getPos(),
				Param::Shout::Radius,
				Param::Shout::Power,
				timeSec
				);
			co_await BehaviorUtil::WaitForSeconds(m_pActor, Param::Shout::WaitTime);
		}

		m_quake->stop();

		co_await BehaviorUtil::WaitForSeconds(m_pActor, timeSec);

		this->changeState<WaitState>();
		co_return;
	}
	void AngryState::update()
	{
	}
}
