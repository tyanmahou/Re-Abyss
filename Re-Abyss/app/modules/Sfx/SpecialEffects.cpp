#include <abyss/modules/Sfx/SpecialEffects.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>
#include <abyss/modules/DrawManager/DrawOrder.hpp>

namespace abyss::Sfx
{
	void SpecialEffects::update(double dt)
	{
		m_flush.update(dt);
		m_skipFade.update(dt);
		m_bossFade.update(dt);
	}
	void SpecialEffects::draw() const
	{
		m_pManager->getModule<DrawManager>()->add(DrawLayer::LightFront, [&] {
			if (m_bossFade.isActive()) {
				m_bossFade.draw();
			}
			if (m_flush.isActive()) {
				m_flush.draw();
			}
			if (m_skipFade.isActive()) {
				m_skipFade.draw();
			}
		}, DrawOrder::LightFront::Flush);
	}
}
