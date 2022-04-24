#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Sfx/Common/ColorFade.hpp>

namespace abyss::Sfx
{
	class SkipFade
	{
	public:
		void start(double time = 1.0, const s3d::ColorF& color = s3d::Palette::Black);
		void start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color = s3d::Palette::Black);
		bool isFadeInEnd() const;
		bool isFadeOutEnd() const;
	public:
		void update(double dt);
		void draw() const;
	private:
		ColorFade m_fade;
	};
}