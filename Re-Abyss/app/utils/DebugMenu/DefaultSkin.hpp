#pragma once
#include <abyss/utils/DebugMenu/ISkin.hpp>
#include <Siv3D/Font.hpp>

namespace abyss::DebugMenu
{
	class IFolder;

	class DefaultSkin : public ISkin
	{
	public:
		DefaultSkin();
	protected:
		virtual s3d::Vec2 drawFolder(const IFolder* pFolder) const;
	private:
		void draw(const RootFolder* pRoot) const override;
	private:
		s3d::Font m_font;
		s3d::Font m_fontHeader;
	};
}