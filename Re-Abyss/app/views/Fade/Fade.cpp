#include "Fade.hpp"


#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>

namespace
{
	Color g_fadeColor = Palette::Black;

	Image CreateImg(const Size& size = Scene::Size(), const Color& color = Palette::White)
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
		return ::FadeBase(Scene::Rect(), t);
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
			Scene::Rect().draw(g_fadeColor);
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
			constexpr uint32 width = static_cast<uint32>(Constants::GameScreenSize.x);
			constexpr uint32 height = static_cast<uint32>(Constants::GameScreenSize.y);
			static RenderTexture rt(width, height);
			static RenderTexture rt2(width, height);
			static const PixelShader ps(U"resources/shaders/not_equal_mask.hlsl" ,{ { U"PSConstants2D", 0 } });

			rt.clear(ColorF(1.0, 1.0));
			{
				ScopedRenderTarget2D target(rt);
				Circle(pos - Constants::GameScreenOffset, Scene::Width() * func(1.0 - t)).draw(Palette::Black);
			}
			rt2.clear(ColorF(0.0, 1.0));
			{
				ScopedRenderTarget2D target(rt2);
				rect.movedBy(-Constants::GameScreenOffset).draw(g_fadeColor);
			}
			Graphics2D::SetTexture(1, rt);
			{
				ScopedCustomShader2D shader(ps);
				rt2.draw(rect.pos);
			}
			//ScopedStencilMask mask(
			//[t,pos]{Circle(pos, Window::BaseWidth() * func(1.0 - t)).draw(); },
			//StencilFunc::NotEqual
			//);
			//rect.draw(g_fadeColor);
		}
	}

	void SetFadeColor(const s3d::Color & color)
	{
		g_fadeColor = color;
	}
}