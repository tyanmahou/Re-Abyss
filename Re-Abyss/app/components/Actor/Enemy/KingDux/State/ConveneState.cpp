#include <abyss/components/Actor/Enemy/KingDux/State/ConveneState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void ConveneState::start()
	{
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
