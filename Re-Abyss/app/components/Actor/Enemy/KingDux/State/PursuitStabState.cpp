#include "PursuitStabState.hpp"

#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Main.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void PursuitStabState::start()
	{
		m_behavior->setActive(false);
		for (const auto& desc : TentacleParam::PursuitStab::Tentacle) {
			m_tentacles << KingDuxUtil::BuildTentacle(m_pActor, desc);
		}
	}
	Task<void> PursuitStabState::task()
	{
		co_await(this->subTask() | this->subTask2());

		this->changeState<WaitState>();
		co_return;
	}
	Task<void> PursuitStabState::subTask()
	{
		// 数秒待つ
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 10.0);

		for (auto&& obj : m_tentacles) {
			if (!obj) {
				continue;
			}
			// リターンリクエスト
			obj->find<Tentacle::Main>()->requestReturn();
		}
		co_await BehaviorUtil::Freeze();
	}
	Task<void> PursuitStabState::subTask2()
	{
		co_await Coro::WaitUntil([&] {
			return m_tentacles.all([](const Ref<ActorObj>& obj) {
				return !obj;
				});
			});
	}
}
