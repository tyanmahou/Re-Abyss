#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/Forward.hpp>
#include <Siv3D/Fwd.hpp>
namespace abyss::Actor::Enemy::CaptainTako::Shot
{
	struct Builder
	{
		static void Build(IActor* pActor, const s3d::Vec2& pos, Forward forward);
	};
}