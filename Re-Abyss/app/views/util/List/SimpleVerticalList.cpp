#include <abyss/views/util/List/SimpleVerticalList.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/utils/Math/Math.hpp>

namespace abyss::UI::List
{
    SimpleVerticalList::SimpleVerticalList():
        m_screen(),
        m_fontSize(16),
        m_fontColor(Palette::Black)
    {
    }
    void SimpleVerticalList::draw() const
    {
        if (!m_pRecords) {
            return;
        }
        auto font = FontAsset(FontName::DebugLog);
        const Vec2 columnSize{ m_screen.w, font.height(m_fontSize) };
        size_t index = 0;
        for (const auto& record: m_pRecords->getList()) {
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
            if (abyss::Math::IsEqualLoose(m_fontSize, static_cast<double>(font.fontSize()))) {
                font(record.title).draw( column, m_fontColor);
            } else {
                font(record.title).draw(m_fontSize, column, m_fontColor);
            }

            if (column.leftReleased() && record.onClick) {
                record.onClick();
            }
            ++index;
        }
    }
}
