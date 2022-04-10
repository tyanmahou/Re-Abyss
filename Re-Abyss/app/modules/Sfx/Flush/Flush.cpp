#include <abyss/modules/Sfx/Flush/Flush.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>
#include <abyss/modules/DrawManager/DrawOrder.hpp>

namespace abyss::Sfx
{
	void Flush::start(double time, const s3d::ColorF& color)
	{
		m_base.start(time, color);
	}
	void Flush::start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color)
	{
		m_base.start(fadeInTime, fadeOutTime, color);
	}
	bool Flush::isFadeInEnd() const
	{
		return m_base.isFadeInEnd();
	}
	bool Flush::isFadeOutEnd() const
	{
		return m_base.isFadeOutEnd();
	}
	void Flush::startFront(double time, const s3d::ColorF& color)
	{
		m_front.start(time, color);
	}
	void Flush::startFront(double fadeInTime, double fadeOutTime, const s3d::ColorF& color)
	{
		m_front.start(fadeInTime, fadeOutTime, color);
	}
	void Flush::update(double dt)
	{
		m_base.update(dt);
		m_front.update(dt);
	}
	void Flush::draw() const
	{
		m_pManager->getModule<DrawManager>()->add(DrawLayer::UI, [&] {
			m_base.draw();
			m_front.draw();
		}, DrawOrder::UI::Flush);
	}
}
