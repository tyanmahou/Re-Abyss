#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Effect/Misc/Bubble/BubbleKind.hpp>
#include <abyss/components/Effect/Misc/Bubble/LayerKind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Effect::Misc::Bubble
{
	struct Builder
	{
		static void Build(EffectObj* pObj, BubbleKind kind, LayerKind layer, const s3d::Optional<s3d::RectF>& area);
	};
}