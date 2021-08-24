#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Effect/Misc/Fish/LayerKind.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Effect::Misc::Fish
{
	struct Builder
	{
		static void Build(EffectObj* pObj, LayerKind layer, const s3d::Optional<s3d::RectF>& area);
	};
}