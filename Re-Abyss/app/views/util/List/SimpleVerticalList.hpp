#pragma once
#include <functional>
#include <Siv3D/RectF.hpp>
#include <Siv3D/String.hpp>
#include <abyss/views/util/List/IContentList.hpp>

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
        SimpleVerticalList& setList(IContentList<Record>* pRecords)
        {
            m_pRecords = pRecords;
            return *this;
        }
        void draw() const;

        SimpleVerticalList& push_back(Record&& record)
        {
            // TODO 削除
            return *this;
        }
    public:
        s3d::RectF m_screen;
        double m_fontSize ;
        s3d::Color m_fontColor;
        IContentList<Record>* m_pRecords;
    };
}
