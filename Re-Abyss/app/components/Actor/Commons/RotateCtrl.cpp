#include "RotateCtrl.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor
{
    RotateCtrl& RotateCtrl::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }
    RotateCtrl& RotateCtrl::addRotate(double rotate)
    {
        m_rotate += rotate;
        return *this;
    }
    double RotateCtrl::getRotate() const
    {
        return m_rotate;
    }

    s3d::Vec2 RotateCtrl::getDir() const
    {
        return s3d::Circular(1.0, m_rotate).toVec2();
    }
    s3d::Vec2 RotateCtrl::getDir0() const
    {
        return s3d::Circular0(1.0, m_rotate).toVec2();
    }    
    s3d::Vec2 RotateCtrl::getDir3() const
    {
        return s3d::Circular3(1.0, m_rotate).toVec2();
    }    
    s3d::Vec2 RotateCtrl::getDir6() const
    {
        return s3d::Circular6(1.0, m_rotate).toVec2();
    }    
    s3d::Vec2 RotateCtrl::getDir9() const
    {
        return s3d::Circular9(1.0, m_rotate).toVec2();
    }
}