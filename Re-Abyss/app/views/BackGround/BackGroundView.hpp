#pragma once

#include <Siv3D/Array.hpp>

#include "BackGroundVM.hpp"
#include "Wave/WaveShader.hpp"
#include "Sky/SkyShader.hpp"

namespace abyss
{
	class BackGroundView
	{
	private:
		s3d::Array<BackGroundVM> m_bgs;
		WaveShader m_waveShader;
		SkyShader m_skyShader;
		s3d::Texture m_skyTexture;
	public:
		BackGroundView();
		void addBackGround(const BackGroundVM& bg);
		void draw(const CameraView& camera)const;
	};
}