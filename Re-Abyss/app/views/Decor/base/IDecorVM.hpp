#pragma once
#include <Siv3D/Rectangle.hpp>

namespace abyss
{
    class IDecorVM
    {
    protected:
        double m_time = 0;
    public:
        void setTime(double time)
        {
            m_time = time;
        }
        virtual void draw(const s3d::RectF& screen) const = 0;
    };
}