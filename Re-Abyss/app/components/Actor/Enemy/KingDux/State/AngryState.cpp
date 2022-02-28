#include <abyss/components/Actor/Enemy/KingDux/State/AngryState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Effect/Misc/ShockWaveDist/Builder.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void AngryState::start()
	{
	}
	void AngryState::end()
	{
	}
	Coro::Task<> AngryState::task()
	{
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.0);
		double timeSec = 3.5;
		m_pActor->getModule<Effects>()->createWorldFront<Effect::Misc::ShockWaveDist::Builder>(
			m_body->getPos(),
			900.0,
			200.0,
			timeSec
			);

		co_await BehaviorUtil::WaitForSeconds(m_pActor, timeSec);

		this->changeState<WaitState>();
		co_return;
	}
	void AngryState::update()
	{
	}
}
