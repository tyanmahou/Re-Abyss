#include <abyss/modules/Sfx/Flush/Flush.hpp>

namespace abyss::Sfx
{
	void Flush::start(double time, const s3d::ColorF& color)
	{
		m_fade.start(time, color);
	}
	void Flush::start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color)
	{
		m_fade.start(fadeInTime, fadeOutTime, color);
	}
	bool Flush::isFadeInEnd() const
	{
		return m_fade.isFadeInEnd();
	}
	bool Flush::isFadeOutEnd() const
	{
		return m_fade.isFadeOutEnd();
	}
	void Flush::update(double dt)
	{
		m_fade.update(dt);
	}
	void Flush::draw() const
	{
		m_fade.draw();
	}
}
