#include <abyss/components/Effect/Actor/Item/Recovery/Builder.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Item/Recovery/LocationCtrl.hpp>
#include <abyss/components/Effect/Actor/Item/Recovery/Circles.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
	void Builder::Build(EffectObj* pObj, const Ref<abyss::Actor::ILocator>& locator)
	{
		// ロケーション制御
		{
			pObj->attach<LocationCtrl>(pObj, locator);
		}
		// 描画
		{
			pObj->attach<Circles>(pObj);
		}
	}
}