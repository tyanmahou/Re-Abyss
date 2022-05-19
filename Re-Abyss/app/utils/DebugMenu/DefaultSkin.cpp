#include <abyss/utils/DebugMenu/DefaultSkin.hpp>
#include <abyss/utils/DebugMenu/IItem.hpp>
#include <abyss/utils/DebugMenu/RootFolder.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	DefaultSkin::DefaultSkin():
		m_font(12, Typeface::Regular),
		m_fontHeader(12, Typeface::Regular, FontStyle::Bold)
	{
	}

	s3d::Vec2 DefaultSkin::drawFolder(const IFolder* pFolder) const
	{
		constexpr auto baseColor = Color(249);
		constexpr auto headerColor = Color(130, 130, 224);
		constexpr auto headerTextColor = Palette::White;
		constexpr auto focusColor = Color(230, 230, 255);
		constexpr auto focusTextColor = Palette::Black;
		constexpr auto textColor = Palette::Black;

		s3d::Array<StringView> labels;
		for (auto&& pNode : pFolder->childNodes()) {
			if (auto pItem = std::dynamic_pointer_cast<IItem>(pNode)) {
				labels << pItem->label();
			}
		}
		// ウィンドウサイズを確定
		Vec2 size{ 100, 0 };
		{
			auto ls = m_fontHeader(pFolder->label()).region().size;
			size.x = s3d::Max(ls.x, size.x);
			size.y += ls.y;
		}
		for (auto&& label : labels) {
			auto ls = m_font(label).region().size;
			size.x = s3d::Max(ls.x, size.x);
			size.y += ls.y;
		}
		size.y = s3d::Max(size.y, 100.0);

		bool isActive = true;
		if (auto focus = pFolder->focusItem()) {
			if (auto childFolder = std::dynamic_pointer_cast<IFolder>(focus.lock())) {
				if (childFolder->isOpened()) {
					isActive = false;
				}
			}
		}
		
		// ウィンドウ描画
		constexpr Vec2 offsetBase{ 5, 5 };
		const Vec2 windowSize = size + offsetBase * 2.0;
		{
			RectF(windowSize).drawShadow(Vec2{ 0, 0 }, 20.0, 2.0, ColorF(baseColor, 0.5))
				.draw(ColorF(baseColor, 1))
				.drawFrame(2.0, focusColor);
		}

		Vec2 offset = offsetBase;
		// ヘッダー
		{
			auto ls = m_fontHeader(pFolder->label()).region().size;
			ls.x = s3d::Max(ls.x, size.x);
			auto rect = RectF(ls + Vec2{ offset.x * 2.0, offset.y - 1 });
			rect.draw(headerColor);
			m_font(pFolder->label()).draw(Vec2{ offset.x, offset.y / 2 }, headerTextColor);
			offset.y = rect.h + 1;
		}

		// 項目
		Vec2 ret{ 100,100 };
		auto selectIndex = pFolder->focusIndex();
		for (auto [index, label] : s3d::Indexed(labels)) {
			bool isSelected = selectIndex && *selectIndex == index;
			if (isSelected) {
				auto ls = m_font(label).region().size;
				ls.x = s3d::Max(ls.x, size.x);
				RectF(offset, ls).draw(focusColor);

				ret = RectF(offset, ls).tr();
			}
			auto region = m_font(label).draw(offset, isSelected ? focusTextColor : textColor);
			offset = region.bl();
		}
		if (!isActive) {
			RectF(windowSize).draw(ColorF(0, 0, 0.2, 0.5));
		}
		return ret;
	}

	void DefaultSkin::draw(const RootFolder* pRoot) const
	{
		Vec2 offset{ 10, 10 };
		const IFolder* folder = pRoot;
		while (folder) {
			Transformer2D transformer(Mat3x2::Translate(offset), s3d::TransformCursor::Yes);
			offset += this->drawFolder(folder) - Vec2{ 10, 10 };
			if (auto focus = folder->focusItem()) {
				if (auto childFolder = std::dynamic_pointer_cast<IFolder>(focus.lock())) {
					if (childFolder->isOpened()) {
						folder = childFolder.get();
						continue;
					}
				}
			}

			break;
		}
	}

}
