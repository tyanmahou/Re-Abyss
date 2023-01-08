#pragma once
#include <abyss/views/FieldEnv/Sky/SkyView.hpp>

namespace abyss::FieldEnv
{
    /// <summary>
    /// 空
    /// </summary>
    class Sky
    {
    public:
        void update(double dt);
        void draw(const s3d::Vec2& pos) const;
    private:
        double m_time = 0.0;
        SkyView m_view;
    };
}
