#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/DeadState.hpp>

#include <abyss/components/Actor/utils/StatePriority.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
	void DeadState::Change(ActorObj* pActor)
	{
		pActor->find<StateCtrl>()->changeState<DeadState, StatePriority::Dead>();
	}
	void DeadState::start()
	{
		// 当たりむこう
		m_colCtrl->setActive(false);
	}
	void DeadState::end()
	{
	}
	Coro::Task<> DeadState::task()
	{
		m_pActor->destroy();
		co_return;
	}
	void DeadState::update()
	{
	}
}