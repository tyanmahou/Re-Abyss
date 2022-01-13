#include "StabState.hpp"

#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/RetireCtrl.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	StabState::StabState(const s3d::Array<TentacleDesc>& desc):
		m_tentacleDesc(desc)
	{}
	void StabState::start()
	{
		m_behavior->setActive(false);
		for (const auto& desc : m_tentacleDesc) {
			m_tentacles << KingDuxUtil::BuildTentacle(m_pActor, desc);
		}
	}
	Task<void> StabState::task()
	{
		co_await (this->subTask() | this->subTask2());

		this->changeState<WaitState>();
		co_return;
	}
	Task<void> StabState::subTask()
	{
		// 数秒待つ
		co_await (BehaviorUtil::WaitForSeconds(m_pActor, 10.0) | Coro::WaitUntil([&] {

			int32 retireCount = 0;
			for (auto&& obj : m_tentacles) {
				if (!obj || obj->find<Tentacle::RetireCtrl>()->isRetire()) {
					++retireCount;
				}
			}
			return retireCount >= 2;
		}));

		for (auto&& obj : m_tentacles) {
			if (!obj) {
				continue;
			}
			// リターンリクエスト
			obj->find<Tentacle::RetireCtrl>()->requestReturn();
		}
		co_await BehaviorUtil::Freeze();
	}
	Task<void> StabState::subTask2()
	{
		co_await Coro::WaitUntil([&] {
			return m_tentacles.all([](const Ref<ActorObj>& obj) {
				return !obj;
			});
		});
	}
}
