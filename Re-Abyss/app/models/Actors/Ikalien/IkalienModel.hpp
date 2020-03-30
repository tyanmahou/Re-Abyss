#pragma once
#include <Siv3D/Fwd.hpp>
namespace abyss
{
    class IkalienModel
    {
    private:
        double m_rotate = 0;
    public:
        IkalienModel& setRotate(double rotate);
        IkalienModel& addRotate(double rotate);
        double getRotate()const;

        s3d::Vec2 getDir() const;
    };
}