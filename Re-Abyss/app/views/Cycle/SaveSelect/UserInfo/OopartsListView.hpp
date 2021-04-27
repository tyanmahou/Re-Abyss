#pragma once
#include <abyss/views/Actor/Ooparts/base/IconView.hpp>

#include <abyss/views/util/OutLine/OutLineShader.hpp>
#include <Siv3D/RenderTexture.hpp>

namespace abyss::Cycle::SaveSelect::UserInfo
{
    class OopartsListView
    {
        Actor::Ooparts::IconView m_icon;
        s3d::Vec2 m_pos;
        double m_offsetX = 10;

        s3d::Array<OopartsType> m_having;

        RenderTexture m_rt;
        OutLineShader m_outLineShader;
    public:
        OopartsListView();

        OopartsListView& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        OopartsListView& setOffsetX(double offset)
        {
            m_offsetX = offset;
            return *this;
        }
        OopartsListView& setHaving(s3d::Array<OopartsType>&& having)
        {
            m_having = std::move(having);
            return *this;
        }
        void draw() const;
    };
}