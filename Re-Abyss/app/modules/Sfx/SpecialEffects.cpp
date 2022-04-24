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
	}
	void SpecialEffects::draw() const
	{
		m_pManager->getModule<DrawManager>()->add(DrawLayer::UI, [&] {
			m_flush.draw();
			m_skipFade.draw();
		}, DrawOrder::UI::Flush);
	}
}
