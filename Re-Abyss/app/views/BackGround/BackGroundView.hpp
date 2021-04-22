#pragma once

#include <Siv3D/Array.hpp>

#include "BackGroundVM.hpp"
#include "Wave/WaveShader.hpp"
#include "Sky/SkyView.hpp"

namespace abyss
{
	class BackGroundView
	{
	private:
		s3d::Array<BackGroundVM> m_bgs;
		WaveShader m_waveShader;
		SkyView m_sky;
		s3d::ColorF m_bgColor;
	public:
		BackGroundView();

		void setTime(double time);

		void addBackGround(const BackGroundVM& bg);
		void setBgColor(const s3d::ColorF& color)
		{
			m_bgColor = color;
		}
		const s3d::ColorF& getBgColor() const
		{
			return m_bgColor;
		}
		void draw(const CameraView& camera)const;
	};
}