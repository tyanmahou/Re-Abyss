#include <abyss/modules/Sfx/SkipFade/SkipFade.hpp>

namespace abyss::Sfx
{
	void SkipFade::start(double time, const s3d::ColorF& color)
	{
		this->start(0.0, time, color);
	}
	void SkipFade::start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color)
	{
		m_fade.start(fadeInTime, fadeOutTime, color);
	}
	bool SkipFade::isFadeInEnd() const
	{
		return m_fade.isFadeInEnd();
	}
	bool SkipFade::isFadeOutEnd() const
	{
		return m_fade.isFadeOutEnd();
	}
	bool SkipFade::isActive() const
	{
		return !isFadeInEnd() || !isFadeOutEnd();
	}
	void SkipFade::update(double dt)
	{
		m_fade.update(dt);
	}
	void SkipFade::draw() const
	{
		m_fade.draw();
	}
}
