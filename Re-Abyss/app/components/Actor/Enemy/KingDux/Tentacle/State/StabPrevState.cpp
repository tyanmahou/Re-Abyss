#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/StabPrevState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/StabState.hpp>

#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	void StabPrevState::start()
	{
	}
	void StabPrevState::end()
	{
	}
	Coro::Task<> StabPrevState::task()
	{
		m_shake->request(10.0, 1.0);

		co_await Coro::WaitWhile([&] {
			return m_shake->isShakeing();
		});

		// 突く
		this->changeState<StabState>();
		co_return;
	}
}
