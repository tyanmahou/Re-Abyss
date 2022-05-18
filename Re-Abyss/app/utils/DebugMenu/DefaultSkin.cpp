#include <abyss/utils/DebugMenu/DefaultSkin.hpp>
#include <abyss/utils/DebugMenu/IItem.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	DefaultSkin::DefaultSkin():
		m_font(15, Typeface::Regular)
	{
	}

	void DefaultSkin::drawBase(const s3d::Vec2& size, bool isActive) const
	{
		constexpr auto baseColor = ColorF(0.3, 0.3, 0.5);
		auto rect = RectF(size);
		rect.drawShadow(Vec2{ 0, 0 }, 24.0, 3.0, ColorF(baseColor, 0.9))
			.draw({ ColorF(baseColor, 0.2), ColorF(baseColor, 0.2), ColorF(0, 0.2), ColorF(0, 0.2) });
		if (isActive) {
			rect.drawFrame(2.0, ColorF(baseColor, 0.5));
		}
	}

	void DefaultSkin::draw(const s3d::Array<std::shared_ptr<INode>>& nodes, const s3d::Optional<size_t> selectIndex) const
	{
		s3d::Array<StringView> labels;
		for (auto&& pNode : nodes) {
			if (auto pItem = std::dynamic_pointer_cast<IItem>(pNode)) {
				labels << pItem->label();
			}
		}
		Vec2 size{ 100, 0 };
		for (auto&& label : labels) {
			auto ls = m_font(label).region().size;
			size.x = s3d::Max(ls.x, size.x);
			size.y += ls.y;
		}
		size.y = s3d::Max(size.y, 100.0);
		Vec2 offset{ 5, 5 };
		drawBase(size + offset * 2, true);

		for (auto [index, label] : s3d::Indexed(labels)) {
			bool isSelected = selectIndex && *selectIndex == index;
			if (isSelected) {
				auto ls = m_font(label).region().size;
				ls.x = s3d::Max(ls.x, size.x);
				RectF(offset, ls).draw(ColorF(1, 0.5));
			}
			auto region = m_font(label).draw(offset, isSelected ? Palette::Black : Palette::White);
			offset = region.bl();
		}
	}

}
