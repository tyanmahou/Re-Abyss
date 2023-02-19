#pragma once
#include <abyss/modules/Camera/CameraTarget/base/ICameraTarget.hpp>

namespace abyss
{
    class CameraTargetBase : public ICameraTarget
    {
    public:
        CameraTargetBase() = default;
        CameraTargetBase(CameraTargetPriority priority):
            m_priority(priority)
        {}

        virtual s3d::Vec2 targetPos() const = 0;

        double zoomScale() const override
        {
            return 1.0;
        }

        CameraTargetPriority priority() const override
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
        CameraTargetPriority m_priority;
        double m_interpRate = 1.0;
        bool m_isActive = true;
        bool m_isEnd = false;
    };
}
