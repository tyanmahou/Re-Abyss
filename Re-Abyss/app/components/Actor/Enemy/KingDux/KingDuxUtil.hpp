#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/params/Actor/Enemy/KingDux/TentacleParam.hpp>
#include <abyss/params/Actor/Enemy/KingDux/BabyDuxParam.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>
namespace abyss::Actor::Enemy::KingDux
{
	struct KingDuxUtil
	{
	public:
		static Ref<ActorObj> BuildTentacle(ActorObj* pActor, const TentacleDesc& desc);

		static Ref<ActorObj> BuildBaby(ActorObj* pActor, const BabyDux::BabyDesc& desc);

		static void SetVisible(ActorObj* pActor, bool isVisible);

		static Coro::Fiber<void> WaitTillStabAction(ActorObj* pActor, const s3d::Array<Ref<ActorObj>>& tentacles);
		static Coro::Fiber<void> WaitTillTentacleRetire(const s3d::Array<Ref<ActorObj>>& tentacles, s3d::int32 count = 2);
		static Coro::Fiber<void> RetireFiber(
			ActorObj* pActor,
			const s3d::Array<Ref<ActorObj>>& tentacles,
			double timeOutSec = 10.0,
			s3d::int32 count = 2
		);
		static Coro::Fiber<void> WaitTillTentacle(const s3d::Array<Ref<ActorObj>>& tentacles);
		static void RequestRetires(const s3d::Array<Ref<ActorObj>>& tentacles);
	};
}
