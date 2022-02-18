#include <abyss/components/Actor/Enemy/KingDux/State/AngryState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>

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
		this->changeState<WaitState>();
		co_return;
	}
	void AngryState::update()
	{
	}
}
