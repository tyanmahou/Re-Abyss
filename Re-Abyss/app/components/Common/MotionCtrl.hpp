#pragma once
#include <abyss/components/base/IComponent.hpp>

namespace abyss
{
    class MotionCtrl : public IComponent
    {
    public:
        template<class T>
        MotionCtrl& set(T motion)
        {
            m_motion = static_cast<s3d::int32>(motion);
            return *this;
        }
        template<class T>
        T get() const
        {
            return static_cast<T>(m_motion);
        }

        MotionCtrl& setAnimeTime(double animeTime)
        {
            m_animeTime = animeTime;
            return *this;
        }
        double animeTime() const
        {
            return m_animeTime;
        }
    protected:
        s3d::int32 m_motion = 0;
        double m_animeTime = 0;
    };
}