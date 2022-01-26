#include <abyss/views/Actor/Player/Shot/ShotEffect.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player::Shot
{
	ShotEffect::ShotEffect(const s3d::Vec2& pos, double r, const s3d::Color& color, Light* pLight) :
		m_pos(pos),
		m_hsv(color),
		m_r(r),
		m_pLight(pLight)
	{
		double offset = Random<double>(0, 10);
		m_r -= offset;

		m_hsv.h += 5 * offset;
	}
	bool ShotEffect::update(double t)
	{
		ScopedRenderStates2D s(BlendState::Additive);
		double revT = 1.0 - t > 0 ? 1.0 - t : 0;
		double r = m_r * revT;
		Circle(m_pos, r).draw(m_hsv.toColor(static_cast<uint32>(50.0 * revT)));

		if (m_pLight) {
			m_pLight->addCircle(m_pos, r * 2.5,  1.0f - (1.0 - revT) * (1.0 - revT));
		}
		return t <= 1.0;
	}

	ShotFiringEffect::ShotFiringEffect(const s3d::Vec2& pos, double r, const s3d::Color& color) :
		m_pos(pos),
		m_color(color),
		m_r(r* r / 2.0)
	{}

	bool ShotFiringEffect::update(double t) 
	{
		t *= 1.7;
		ScopedRenderStates2D s(BlendState::Additive);
		double rate = EaseOut(Easing::Quint, t);
		Color color = m_color.setA(static_cast<uint32>(128.0 * Max(1 - t, 0.0)));
		Circle(m_pos, rate * m_r).drawFrame(1, 1, color);
		return t <= 1.0;
	}
}
