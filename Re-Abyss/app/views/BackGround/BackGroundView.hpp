#pragma once

#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include "BackGroundVM.hpp"

namespace abyss
{
	class BackGroundView
	{
	private:
		s3d::Array<BackGroundVM> m_bgs;
	public:
		BackGroundView();
		void addBackGround(const BackGroundVM& bg);
		void draw(const CameraView& camera)const;
	};
}