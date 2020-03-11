#pragma once

#include <Siv3D/Array.hpp>

#include "BackGroundVM.hpp"

namespace abyss
{
	class BackGroundView
	{
	private:
		s3d::Array<BackGroundVM> m_bgs;
	public:
		void addBackGround(const BackGroundVM& bg);
		void draw(const s3d::Vec2& pos)const;
	};
}