#include <abyss/views/util/List/SimpleVerticalList.hpp>
#include <abyss/commons/FontName.hpp>

namespace abyss::UI::List
{
    void SimpleVerticalList::draw() const
    {
        auto font = FontAsset(FontName::DebugLog);
        const Vec2 columnSize{ m_screen.w, font.height(m_fontSize) };
        size_t index = 0;
        for (const auto& record: m_records) {
            RectF column(0, columnSize.y * index, columnSize);
            ColorF color(record.backGroundColor);
            if (column.mouseOver()) {
                HSV hsv(color);
                hsv.s += 0.1;
                hsv.v -= 0.1;
                color = hsv;
                s3d::Cursor::RequestStyle(CursorStyle::Hand);
            }
            column.draw(color.setA(0.9));
            font(record.title).draw(m_fontSize, column, Palette::Black);

            if (column.leftReleased() && record.onClick) {
                record.onClick();
            }
            ++index;
        }
    }
}
