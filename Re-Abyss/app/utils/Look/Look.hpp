#pragma once
#include <abyss/entities/Forward.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    class Look
    {
    public:
        Look();
        Look(double x, double y);
        Look(const s3d::Vec2& v);

        bool isForward(Forward f) const;

        Forward verticalForward() const;
        Forward horizonalForward() const;
    private:
        s3d::Vec2 m_value;
    };
}