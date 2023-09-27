#pragma once
#include <functional>
#include <Siv3D/RectF.hpp>
#include <Siv3D/String.hpp>
#include <abyss/views/util/List/IEnumerable.hpp>

namespace abyss::UI::List
{
    class SimpleVerticalList
    {
    public:
        struct Record
        {
            s3d::String title;
            std::function<void()> onClick;
            s3d::Color backGroundColor;
        };
        using IEnumerable = IEnumerable<Record>;
    public:
        SimpleVerticalList();

        SimpleVerticalList& setScreen(const s3d::RectF& screen)
        {
            m_screen = screen;
            return *this;
        }
        SimpleVerticalList& setFontSize(double size)
        {
            m_fontSize = size;
            return *this;
        }
        SimpleVerticalList& setFontColor(const s3d::Color color)
        {
            m_fontColor = color;
            return *this;
        }
        SimpleVerticalList& setList(const IEnumerable* pRecords)
        {
            m_pRecords = pRecords;
            return *this;
        }
        void draw() const;
    public:
        s3d::RectF m_screen;
        double m_fontSize ;
        s3d::Color m_fontColor;
        const IEnumerable* m_pRecords;
    };
}
