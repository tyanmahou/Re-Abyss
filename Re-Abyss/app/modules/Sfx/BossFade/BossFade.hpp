#pragma once
#include <Siv3D/ColorF.hpp>
#include <Siv3D/Palette.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Sfx
{
	/// <summary>
	/// Bossフェード
	/// </summary>
	class BossFade
	{
	public:
		void start(
			double fadeInTime = 6.0,
			double fadeWaitTime = 2.0,
			double fadeOutTime = 1.0
		);
		bool isFadeInEnd() const;
		bool isFadeOutEnd() const;

		void update(double dt);
		void draw() const;
	private:
		TimeLite::Timer m_fadeInTimer;
		TimeLite::Timer m_fadeWaitTimer;
		TimeLite::Timer m_fadeOutTimer;
		s3d::ColorF m_fadeColor{ 1, 0 };
	};
}