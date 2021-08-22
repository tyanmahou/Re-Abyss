#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Effect/Bubble/BubbleKind.hpp>
#include <abyss/components/Effect/Bubble/LayerKind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Effect::Bubble
{
	struct Builder
	{
		static void Build(EffectObj* pObj, BubbleKind kind, LayerKind layer);
	};
}