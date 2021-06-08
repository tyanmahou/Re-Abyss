#pragma once
#include "ICameraTarget.hpp"

namespace abyss
{
    class CameraTargetBase : public ICameraTarget
    {
    public:
        CameraTargetBase() = default;
        CameraTargetBase(CameraTargetPriorityType priority):
            m_priority(priority)
        {}

        virtual s3d::Vec2 targetPos() const = 0;

        CameraTargetPriorityType priority() const override
        {
            return m_priority;
        }
        void setInterpRate(double rate)
        {
            m_interpRate = rate;
        }
        double interpRate() const override
        {
            return m_interpRate;
        }
        void setActive(bool isActive)
        {
            m_isActive = isActive;
        }
        bool isActive() const override
        {
            return m_isActive;
        }
        void destory()
        {
            m_isEnd = true;
        }
        bool isEnd() const override
        {
            return m_isEnd;
        }
    private:
        CameraTargetPriorityType m_priority;
        double m_interpRate = 1.0;
        bool m_isActive = true;
        bool m_isEnd = false;
    };
}