#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Effect::Actor::Player::ShotFiring
{
	struct Builder
	{
		static void Build(
			EffectObj* pObj,
			const s3d::Vec2& pos,
			double radius,
			const s3d::ColorF& color
			);
	};
}