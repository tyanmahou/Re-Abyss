#pragma once
#include <abyss/components/base/IComponent.hpp>

namespace abyss
{
    class MotionCtrl : public IComponent
    {
    public:
        template<class T>
        void set(T motion)
        {
            m_motion = static_cast<s3d::int32>(motion);
        }
        template<class T>
        T get() const
        {
            return static_cast<T>(m_motion);
        }
    protected:
        s3d::int32 m_motion;
    };
}