#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Triangle.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	class TentacleUtil
	{
	public:
		/// <summary>
		/// コライダーを取得
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="angle"></param>
		/// <returns></returns>
		static s3d::Triangle Shape(const s3d::Vec2& pos, double angle);

		static s3d::Triangle Shape(ActorObj* pActor);
	};
}