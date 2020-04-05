#include "RotateModel.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    RotateModel& RotateModel::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }
    RotateModel& RotateModel::addRotate(double rotate)
    {
        m_rotate += rotate;
        return *this;
    }
    double RotateModel::getRotate() const
    {
        return m_rotate;
    }

    s3d::Vec2 RotateModel::getDir() const
    {
        return s3d::Circular(1.0, m_rotate).toVec2();
    }
    s3d::Vec2 RotateModel::getDir0() const
    {
        return s3d::Circular0(1.0, m_rotate).toVec2();
    }    
    s3d::Vec2 RotateModel::getDir3() const
    {
        return s3d::Circular3(1.0, m_rotate).toVec2();
    }    
    s3d::Vec2 RotateModel::getDir6() const
    {
        return s3d::Circular6(1.0, m_rotate).toVec2();
    }    
    s3d::Vec2 RotateModel::getDir9() const
    {
        return s3d::Circular9(1.0, m_rotate).toVec2();
    }
}