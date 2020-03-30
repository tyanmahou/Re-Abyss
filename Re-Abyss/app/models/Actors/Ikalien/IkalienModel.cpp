#include "IkalienModel.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    IkalienModel& IkalienModel::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }
    IkalienModel& IkalienModel::addRotate(double rotate)
    {
        m_rotate += rotate;
        return *this;
    }
    double IkalienModel::getRotate() const
    {
        return m_rotate;
    }

    s3d::Vec2 IkalienModel::getDir() const
    {
        return s3d::Circular(1.0, m_rotate).toVec2();
    }

}