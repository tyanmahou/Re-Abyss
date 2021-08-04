#pragma once
#include <abyss/views/Env/Sky/SkyView.hpp>

namespace abyss::Env
{
    /// <summary>
    /// 空
    /// </summary>
    class Sky
    {
    public:
        void draw(const s3d::Vec2& pos) const;
    private:
        SkyView m_view;
    };
}