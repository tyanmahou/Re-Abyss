#include <abyss/components/Actor/Enemy/KingDux/State/ConveneState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>

#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void ConveneState::start()
	{
		KingDuxUtil::BuildBaby(m_pActor, BabyDuxParam::Convene::Baby);
	}
	void ConveneState::end()
	{
	}
	Coro::Task<> ConveneState::task()
	{
		this->changeState<WaitState>();
		co_return;
	}
	void ConveneState::update()
	{
	}
}
