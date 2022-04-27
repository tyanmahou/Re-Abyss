#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Sfx/Common/ColorFade.hpp>

namespace abyss::Sfx
{
	class Flush
	{
	public:
		void start(double time = 1.0, const s3d::ColorF& color = s3d::Palette::White);
		void start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color = s3d::Palette::White);
		bool isFadeInEnd() const;
		bool isFadeOutEnd() const;

		bool isActive() const;
	public:
		void update(double dt);
		void draw() const;
	private:
		ColorFade m_fade;
	};
}