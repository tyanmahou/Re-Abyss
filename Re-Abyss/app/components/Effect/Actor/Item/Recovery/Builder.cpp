#include <abyss/components/Effect/Actor/Item/Recovery/Builder.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Item/Recovery/Main.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
	void Builder::Build(EffectObj* pObj, const Ref<abyss::Actor::ILocator>& locator)
	{
		pObj->attach<Main>(pObj, locator);
	}
}