#pragma once
#include<Siv3D.hpp>
#include "../../../application/util/ScopedState.hpp"
namespace abyss
{
	struct PlayerShotEffect : IEffect
	{
	private:
		Vec2 m_pos;
		HSV m_hsv;
		double m_r;
	public:
		PlayerShotEffect(Vec2 pos, double r, const Color& color) :
			m_pos(pos),
			m_hsv(color),
			m_r(r)
		{
			double offset = Random<double>(0, 10);
			m_r -= offset;
	
			m_hsv.h += 5 * offset;
		}

		bool update(double t) override
		{
			ScopedRenderStates2D s(BlendState::Additive);
			double revT = 1.0 - t > 0 ? 1.0 - t : 0;
			double r = m_r * revT;
			Circle(m_pos, r).draw(m_hsv.toColor(static_cast<uint32>(50.0 * revT)));

			return t <= 1.0;
		}
	};

	struct PlayerShotFiringEffect : IEffect
	{
	private:
		Vec2 m_pos;
		Color m_color;
		double m_r;
	public:
		PlayerShotFiringEffect(Vec2 pos, double r, const Color& color) :
			m_pos(pos),
			m_color(color),
			m_r(r * r / 2.0)
		{}

		bool update(double t) override
		{
			t *= 1.7;
			ScopedRenderStates2D s(BlendState::Additive);
			double rate = Easing::EaseOut(Easing::Quint, t);
			Color color = m_color.setAlpha(static_cast<uint32>(128.0 * Max(1 - t, 0.0)));
			Circle(m_pos,  rate * m_r).drawFrame(1,1, color);
			return t <= 1.0;
		}
	};
}