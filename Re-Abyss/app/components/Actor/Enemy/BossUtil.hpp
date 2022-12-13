#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy
{
	/// <summary>
	/// Bossのユーティリティ
	/// </summary>
	class BossUtil
	{
	public:
		// 死亡デモ
		static Coro::Fiber<> DeadDemo(ActorObj* pActor);

	private:
		// 死亡エフェクトをリクエスト
		static Ref<Effect::EffectObj> RequestDeadEffect(ActorObj* pActor, const s3d::Vec2& pos);
	};
}