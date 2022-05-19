#pragma once
#include <abyss/utils/DebugMenu/ISkin.hpp>
#include <Siv3D/Font.hpp>

namespace abyss::DebugMenu
{
	class DefaultSkin : public ISkin
	{
	public:
		DefaultSkin();
	private:
		void draw(const IFolder* pFolder) const override;
	private:
		s3d::Font m_font;
	};
}