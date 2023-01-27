#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/values/Forward.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const s3d::Vec2& pos, Forward forward);
	};
}