#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::Cycle::Title::Logo
{
    /// <summary>
    /// タイトルロゴ
    /// </summary>
    class LogoVM
    {
    private:
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;

        double m_alpha = 1.0f;
    public:
        LogoVM();

        LogoVM& setAlpha(double alpha0_1)
        {
            m_alpha = alpha0_1;
            return *this;
        }
        LogoVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }

        void draw() const;
    };
}