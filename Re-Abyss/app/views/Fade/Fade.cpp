#include "Fade.hpp"


#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/util/MaskUtil/MaskUtil.hpp>
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
			auto mask = MaskUtil::Instance().notEqual([&] {
				auto alpha = EaseInOut(Easing::Linear, 1.0 - t);
				Circle(pos, Scene::Width() * func(1.0 - t)).draw(ColorF(0, alpha));
			});
			rect.movedBy(-Constants::GameScreenOffset).draw(g_fadeColor);
		}
	}

	void SetFadeColor(const s3d::Color & color)
	{
		g_fadeColor = color;
	}
}