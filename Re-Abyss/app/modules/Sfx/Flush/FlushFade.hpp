#pragma once
#include <Siv3D/ColorF.hpp>
#include <Siv3D/Palette.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Sfx
{
	class FlushFade
	{
	public:
		void start(double time = 1.0, const s3d::ColorF& color = s3d::Palette::White);
		void start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color = s3d::Palette::White);
		bool isFadeInEnd() const;
		bool isFadeOutEnd() const;

		void update(double dt);
		void draw() const;
	private:
		bool isFadeIn = false;
		TimeLite::Timer m_fadeInTimer;
		TimeLite::Timer m_fadeOutTimer;
		s3d::ColorF m_fadeColor{1, 0};
	};
}