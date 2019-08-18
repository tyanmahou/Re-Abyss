#include "Fade.hpp"
#include "../../util/ScopedState.hpp"

#include <Siv3D.hpp>

namespace
{
	Color g_fadeColor = Palette::Black;

	Image CreateImg(const Size& size = Window::BaseSize(), const Color& color = Palette::White)
	{
		Image img(size);
		img.fill(color);
		return std::move(img);
	}

	//微調整
	bool FadeBase(const s3d::RectF& rect, double& t)
	{
		if (t > 0.75)
		{
			rect.draw(g_fadeColor);
			return false;
		}

		t *= (1 / 0.75);
		return true;
	}
	bool FadeBase(double& t)
	{
		return ::FadeBase(Window::ClientRect(), t);
	}

}

namespace abyss
{
	namespace Fade
	{
		//デフォルト
		void Default(double t)
		{
			if (!::FadeBase(t))
				return;
			Window::BaseClientRect().draw(g_fadeColor);
		}

		//3次関数的に広がる円形マスク
		void SmoothCircle(double t, const s3d::RectF& rect, const s3d::Vec2& pos)
		{
			if (!::FadeBase(rect, t))
			{
				return;
			}
			static auto func = [=](double t)
			{
				return ((t - 0.3f) * (t - 0.3f) * (t - 0.3f) + 0.027) / 0.37f;
			};

			ScopedStencilMask mask(
			[t,pos]{Circle(pos, Window::BaseWidth() * func(1.0 - t)).draw(); },
			StencilFunc::NotEqual
			);
			rect.draw(g_fadeColor);
		}
	}

	void SetFadeColor(const s3d::Color & color)
	{
		g_fadeColor = color;
	}
}