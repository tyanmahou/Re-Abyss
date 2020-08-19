#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::Cycle::Splash
{
    /// <summary>
    /// スプラッシュロゴ
    /// </summary>
    class LogoVM
    {
    private:
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;

        double m_time0_1 = 0.0f;
    public:
        LogoVM();

        LogoVM& setTime(double time)
        {
            m_time0_1 = time;
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