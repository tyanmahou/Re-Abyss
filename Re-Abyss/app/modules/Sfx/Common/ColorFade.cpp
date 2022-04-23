#include <abyss/modules/Sfx/Common/ColorFade.hpp>
#include <Siv3D.hpp>

namespace abyss::Sfx
{
	void ColorFade::start(double time, const s3d::ColorF& color)
	{
		this->start(time / 2.0, time / 2.0, color);
	}
	void ColorFade::start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color)
	{
		m_fadeColor = color;
		m_fadeColor.a = 0;
		m_fadeInTimer.reset(fadeInTime);
		m_fadeOutTimer.reset(fadeOutTime);
	}
	bool ColorFade::isFadeInEnd() const
	{
		return m_fadeInTimer.isEnd();
	}
	bool ColorFade::isFadeOutEnd() const
	{
		return m_fadeOutTimer.isEnd();
	}
	void ColorFade::update(double dt)
	{
		dt = m_fadeInTimer.update(dt);
		dt = m_fadeOutTimer.update(dt);

		if (!m_fadeInTimer.isEnd()) {
			m_fadeColor.a = m_fadeInTimer.rate();
		} else if (!m_fadeOutTimer.isEnd()) {
			m_fadeColor.a = m_fadeOutTimer.invRate();
		} else {
			m_fadeColor.a = 0;
		}
	}
	void ColorFade::draw() const
	{
		if (m_fadeColor.a <= 0) {
			return;
		}
		s3d::Transformer2D t2d(s3d::Mat3x2::Identity(), s3d::Transformer2D::Target::SetLocal);
		s3d::Scene::Rect().draw(m_fadeColor);
	}
}
