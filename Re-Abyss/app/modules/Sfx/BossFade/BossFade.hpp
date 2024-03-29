#pragma once
#include <Siv3D/ColorF.hpp>
#include <Siv3D/Palette.hpp>
#include <Siv3D/RenderTexture.hpp>
#include <Siv3D/ScopedRenderTarget2D.hpp>
#include <abyss/views/Shader/Mask/MaskShader.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Sfx
{
	/// <summary>
	/// Bossフェード
	/// </summary>
	class BossFade
	{
	public:
		BossFade();

		void start(
			double fadeInTime = 6.0,
			double fadeWaitTime = 2.0,
			double fadeOutTime = 1.0
		);
		bool isFadeInEnd() const;
		bool isFadeOutEnd() const;

		double getFadeInRate() const;
		double getFadeWaitRate() const;
		double getFadeOutRate() const;

		bool isActive() const;

		void update(double dt);
		void draw() const;

		s3d::ScopedRenderTarget2D record() const;
	private:
		TimeLite::Timer m_fadeInTimer;
		TimeLite::Timer m_fadeWaitTimer;
		TimeLite::Timer m_fadeOutTimer;
		s3d::ColorF m_fadeColor{ 1, 0 };

		s3d::RenderTexture m_mask;
		MaskShader m_shader;
	};
}