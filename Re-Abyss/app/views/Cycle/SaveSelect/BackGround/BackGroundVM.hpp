#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::Cycle::SaveSelect::BackGround
{
    /// <summary>
    /// 背景
    /// </summary>
    class BackGroundVM
    {
    private:
        s3d::Texture m_texture;
        s3d::Texture m_fade;
        s3d::Texture m_horizon;
        s3d::Vec2 m_pos;
    public:
        BackGroundVM();

        BackGroundVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }

        void draw(const s3d::Color& color) const;
    };
}