#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Effect::Actor::Breath
{
	struct Builder
	{
		static void Build(EffectObj* pObj, const s3d::Vec2& pos);
	};
}