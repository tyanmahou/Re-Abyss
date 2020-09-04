#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
namespace abyss
{
    class RotateModel : public IComponent
    {
    private:
        double m_rotate = 0;
    public:
        RotateModel& setRotate(double rotate);
        RotateModel& addRotate(double rotate);
        double getRotate()const;

        s3d::Vec2 getDir() const;
        s3d::Vec2 getDir0() const;
        s3d::Vec2 getDir3() const;
        s3d::Vec2 getDir6() const;
        s3d::Vec2 getDir9() const;

    };
}