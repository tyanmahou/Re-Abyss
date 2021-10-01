#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Vector2D.hpp>
#include <abyss/components/Effect/Actor/Ooparts/Common/KiraKira/Type.hpp>

namespace abyss::Effect::Actor::Ooparts::KiraKira
{
	struct Builder
	{
		static void Build(EffectObj* pObj, const s3d::Vec2& pos, Type type = Type::Type1);
	};
}