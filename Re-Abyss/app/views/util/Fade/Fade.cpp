#include <abyss/views/util/Fade/Fade.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/util/MaskUtil/MaskUtil.hpp>

namespace
{
	Color g_fadeColor(35, 50, 80);

	Image CreateImg(const Size& size = Scene::Size(), const Color& color = Palette::White)
	{
		Image img(size);
		img.fill(color);
		return std::move(img);
	}

	//微調整
	bool FadeBase(const s3d::RectF& rect, double& t)
	{
		if (t > 0.75) {
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
			if (!::FadeBase(t)) {
				return;
			}
			Scene::Rect().draw(g_fadeColor);
		}

		//3次関数的に広がる円形マスク
		void IrisOutRect(double t, const s3d::Vec2& pos, const  s3d::RectF& rect)
		{
			if (!::FadeBase(rect, t)) {
				return;
			}
			static auto easing = [](double t) {
				return ((t - 0.3f) * (t - 0.3f) * (t - 0.3f) + 0.027) / 0.37f;
			};
			auto mask = MaskUtil::Instance().notEqual([&] {
				auto alpha = EaseInOut(Easing::Linear, 1.0 - t);
				Circle(pos, rect.w * easing(1.0 - t)).draw(ColorF(0, alpha));
			});
			rect.draw(g_fadeColor);
		}
		void IrisOut(double t, const s3d::Vec2& pos)
		{
			IrisOutRect(t, pos, Scene::Rect());
		}
	}

	void SetFadeColor(const s3d::Color & color)
	{
		g_fadeColor = color;
	}
}