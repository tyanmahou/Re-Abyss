#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::UI::GamePause::BackGround
{
    /// <summary>
    /// 背景
    /// </summary>
    class BackGroundVM
    {
    public:
        BackGroundVM();

        BackGroundVM& setBgColor(const s3d::ColorF& color)
        {
            m_bgColor = color;
            return *this;
        }

        void draw() const;
    private:
        s3d::Texture m_texture;
        s3d::Texture m_horizon;
        s3d::Vec2 m_pos;
        s3d::ColorF m_bgColor;
    };
}
