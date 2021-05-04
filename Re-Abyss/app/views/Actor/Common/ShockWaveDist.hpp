#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Effect.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    struct ShockWaveDist : s3d::IEffect
    {
    public:
        ShockWaveDist(Manager* pManager, const s3d::Vec2& pos, double radius);

        bool update(double t)override;
    private:
        Manager* m_pManager;
        s3d::Vec2 m_pos;
        double m_radius;
    };
}