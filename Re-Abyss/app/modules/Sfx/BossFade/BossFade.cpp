#include <abyss/modules/Sfx/BossFade/BossFade.hpp>

#include <abyss/commons/Constants.hpp>

#include <Siv3D.hpp>

namespace abyss::Sfx
{
	BossFade::BossFade() :
		m_mask(Constants::GameScreenSize.asPoint()),
		m_shader(Constants::GameScreenSize.asPoint())
	{
	}
	void BossFade::start(
		double fadeInTime,
		double fadeWaitTime,
		double fadeOutTime
	) {
		m_fadeColor = s3d::ColorF(0, 0);
		m_fadeInTimer.reset(fadeInTime);
		m_fadeWaitTimer.reset(fadeWaitTime);
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
	double BossFade::getFadeInRate() const
	{
		return m_fadeInTimer.rate();
	}
	double BossFade::getFadeWaitRate() const
	{
		return m_fadeWaitTimer.rate();
	}
	double BossFade::getFadeOutRate() const
	{
		return m_fadeOutTimer.rate();
	}
	bool BossFade::isActive() const
	{
		return !m_fadeInTimer.isEnd()
			|| !m_fadeWaitTimer.isEnd()
			|| !m_fadeOutTimer.isEnd();
	}
	void BossFade::update(double dt)
	{
		m_mask.clear(ColorF(0, 0));

		dt = m_fadeInTimer.update(dt);
		dt = m_fadeWaitTimer.update(dt);
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

		auto scopedMask = m_shader.notEqual([&] {
			m_mask.draw();
		});

		RectF(Constants::GameScreenSize).draw(m_fadeColor);
	}
	s3d::ScopedRenderTarget2D BossFade::record() const
	{
		return s3d::ScopedRenderTarget2D(m_mask);
	}
}
