#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/params/Actor/Enemy/KingDux/TentacleParam.hpp>
#include <abyss/params/Actor/Enemy/KingDux/BabyDuxParam.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>
namespace abyss::Actor::Enemy::KingDux
{
	struct KingDuxUtil
	{
	public:
		static Ref<ActorObj> BuildTentacle(ActorObj* pActor, const TentacleDesc& desc);

		static Ref<ActorObj> BuildBaby(ActorObj* pActor, const BabyDesc& desc);

		static void SetVisible(ActorObj* pActor, bool isVisible);

		static Coro::Task<void> WaitTillStabAction(ActorObj* pActor, const s3d::Array<Ref<ActorObj>>& tentacles);
		static Coro::Task<void> WaitTillTentacleRetire(const s3d::Array<Ref<ActorObj>>& tentacles, s3d::int32 count = 2);
		static Coro::Task<void> RetireTask(
			ActorObj* pActor,
			const s3d::Array<Ref<ActorObj>>& tentacles,
			double timeOutSec = 10.0,
			s3d::int32 count = 2
		);
		static Coro::Task<void> WaitTillTentacle(const s3d::Array<Ref<ActorObj>>& tentacles);
	};
}