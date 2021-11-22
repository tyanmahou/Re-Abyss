#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <concepts>

namespace abyss
{
    template<class T>
    concept MotionKindType = std::integral<T> || std::is_enum_v<T>;

    class MotionCtrl : public IComponent
    {
    public:
        template<MotionKindType T>
        MotionCtrl& set(T motion)
        {
            m_motion = static_cast<s3d::int32>(motion);
            return *this;
        }
        template<MotionKindType T>
        T get() const
        {
            return static_cast<T>(m_motion);
        }

        template<MotionKindType T>
        bool is(T motion)
        {
            return m_motion == static_cast<s3d::int32>(motion);
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