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
		void drawBase(const s3d::Vec2& size, bool isActive) const;
	private:
		void draw(const s3d::Array<std::shared_ptr<INode>>& nodes, const s3d::Optional<size_t> selectIndex) const override;
	private:
		s3d::Font m_font;
	};
}