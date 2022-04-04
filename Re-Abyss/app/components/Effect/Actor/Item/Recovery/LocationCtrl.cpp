#include <abyss/components/Effect/Actor/Item/Recovery/LocationCtrl.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
	LocationCtrl::LocationCtrl(EffectObj* pObj, const Ref<abyss::Actor::ILocator>& locator):
		m_pObj(pObj),
		m_locator(locator)
	{
		if (m_locator) {
			m_pos = m_locator->getCenterPos();
		}
	}
	const s3d::Vec2& LocationCtrl::getPos() const
	{
		return m_pos;
	}
	void LocationCtrl::onUpdate()
	{
		if (m_locator) {
			m_pos = m_locator->getCenterPos();
		}
	}
}