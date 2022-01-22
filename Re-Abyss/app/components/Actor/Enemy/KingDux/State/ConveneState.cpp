#include "ConveneState.hpp"
#include "WaitState.hpp"

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
