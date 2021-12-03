#include "Flush.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>
#include <abyss/modules/DrawManager/DrawOrder.hpp>

namespace abyss::Sfx
{
	void Flush::start(double time, const s3d::ColorF& color)
	{
		m_flush.start(time, color);
	}
	void Flush::start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color)
	{
		m_flush.start(fadeInTime, fadeOutTime, color);
	}
	bool Flush::isFadeInEnd() const
	{
		return m_flush.isFadeInEnd();
	}
	bool Flush::isFadeOutEnd() const
	{
		return m_flush.isFadeOutEnd();
	}
	void Flush::update(double dt)
	{
		m_flush.update(dt);
	}
	void Flush::draw() const
	{
		m_pManager->getModule<DrawManager>()->add(DrawLayer::UI, [&] {
			m_flush.draw();
		}, DrawOrder::UI::Flush);
	}
}
