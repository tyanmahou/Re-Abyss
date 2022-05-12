#include <abyss/components/Effect/Common/EmissiveCtrl.hpp>

#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Light/Light.hpp>

#include <Siv3D.hpp>

namespace abyss::Effect
{
	EmissiveCtrl::EmissiveCtrl(EffectObj* pObj) :
		m_pObj(pObj)
	{
	}
	void EmissiveCtrl::onStart()
	{
		m_drawer = m_pObj->find<Drawer>();
	}
	DrawLayer EmissiveCtrl::getLayer() const
	{
		return m_drawer->getLayer();
	}
	double EmissiveCtrl::getOrder() const
	{
		return m_drawer->getOrder();
	}
	void EmissiveCtrl::onDraw() const
	{
		auto* pLight = m_pObj->getModule<Light>();
		pLight->add([this](double) {
			if (m_drawer) {
				ScopedColorAdd2D scopedColorAdd(ColorF(1, 0));
				m_drawer->onDraw();
			}
		});
	}
}