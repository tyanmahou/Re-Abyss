#include <abyss/modules/Sfx/BossFade/BossFade.hpp>
#include <Siv3D.hpp>

namespace abyss::Sfx
{
	void BossFade::start(double fadeInTime, double fadeOutTime)
	{
		m_fadeColor = s3d::ColorF(0, 0);
		m_fadeInTimer.reset(fadeInTime);
		m_fadeOutTimer.reset(fadeOutTime);
	}
	bool BossFade::isFadeInEnd() const
	{
		return m_fadeInTimer.isEnd();
	}
	bool BossFade::isFadeOutEnd() const
	{
		return m_fadeOutTimer.isEnd();
	}
	void BossFade::update(double dt)
	{
		dt = m_fadeInTimer.update(dt);
		dt = m_fadeOutTimer.update(dt);

		if (!m_fadeInTimer.isEnd()) {
			auto rate = m_fadeInTimer.rate();
			m_fadeColor.b = s3d::Saturate(rate * 3.0);
			m_fadeColor.g = s3d::Saturate(rate * 3.0 - 1.0);
			m_fadeColor.r = s3d::Saturate(rate * 3.0 - 2.0);
			m_fadeColor.a = rate;
		} else if (!m_fadeOutTimer.isEnd()) {
			m_fadeColor.a = m_fadeOutTimer.invRate();
		} else {
			m_fadeColor.a = 0;
		}
	}

	void BossFade::draw() const
	{
		if (m_fadeColor.a <= 0) {
			return;
		}
		s3d::Transformer2D t2d(s3d::Mat3x2::Identity(), s3d::Transformer2D::Target::SetLocal);
		s3d::Scene::Rect().draw(m_fadeColor);
	}
}
