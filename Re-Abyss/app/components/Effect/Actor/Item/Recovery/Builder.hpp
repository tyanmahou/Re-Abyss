#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
	struct Builder
	{
		static void Build(EffectObj* pObj, const Ref<abyss::Actor::ILocator>& locator);
	};
}