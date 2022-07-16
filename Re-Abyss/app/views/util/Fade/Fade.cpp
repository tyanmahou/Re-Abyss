#include <abyss/views/util/Fade/Fade.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/Shader/Mask/MaskShader.hpp>

namespace abyss
{
	class Fade::Impl
	{
	public:
		Impl():
			m_maskShader(Constants::AppResolution)
		{}


		//微調整
		bool fadeBase(const s3d::RectF& rect, double& t)
		{
			if (t > 0.75) {
				rect.draw(m_fadeColor);
				return false;
			}

			t *= (1 / 0.75);
			return true;
		}
		bool fadeBase(double& t)
		{
			return fadeBase(Scene::Rect(), t);
		}
		void defaultFade(double t)
		{
			if (!fadeBase(t)) {
				return;
			}
			Scene::Rect().draw(ColorF(m_fadeColor, t));
		}
		void irisOutRect(double t, const s3d::Vec2& pos, const  s3d::RectF& rect)
		{
			if (!fadeBase(rect, t)) {
				return;
			}
			static auto easing = [](double t) {
				return ((t - 0.3f) * (t - 0.3f) * (t - 0.3f) + 0.027) / 0.37f;
			};
			auto mask = m_maskShader.notEqual([&] {
				auto alpha = EaseInOut(Easing::Linear, 1.0 - t);
				Circle(pos, rect.w * easing(1.0 - t)).draw(ColorF(0, alpha));
				});
			rect.draw(m_fadeColor);
		}

		void setFadeColor(const s3d::Color& color)
		{
			m_fadeColor = color;
		}
	private:
		Color m_fadeColor{ 35, 50, 80 };

		MaskShader m_maskShader;
	};

    Fade::Fade() :
		m_pImpl(std::make_unique<Impl>())
	{}
	Fade::~Fade()
	{
	}
	//デフォルト
	void Fade::Default(double t)
	{
		Instance()->m_pImpl->defaultFade(t);
	}
	//3次関数的に広がる円形マスク
	void  Fade::IrisOutRect(double t, const s3d::Vec2& pos, const  s3d::RectF& rect)
	{
		Instance()->m_pImpl->irisOutRect(t, pos, rect);
	}
	void Fade::IrisOut(double t, const s3d::Vec2& pos)
	{
		Instance()->m_pImpl->irisOutRect(t, pos, Scene::Rect());
	}

    void Fade::SetColor(const s3d::ColorF& color)
    {
        Instance()->m_pImpl->setFadeColor(color);
    }

}
