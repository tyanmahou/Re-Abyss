#pragma once

#include <Siv3D/Array.hpp>

#include "BackGroundVM.hpp"
#include "Wave/WaveShader.hpp"

namespace abyss
{
	class BackGroundView
	{
	private:
		s3d::Array<BackGroundVM> m_bgs;
		WaveShader m_waveShader;
	public:
		void addBackGround(const BackGroundVM& bg);
		void draw(const CameraView& camera)const;
	};
}