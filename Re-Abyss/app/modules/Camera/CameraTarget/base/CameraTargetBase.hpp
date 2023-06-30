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
        void setActive(bool isActive)
        {
            m_isActive = isActive;
        }
        bool isActive() const override
        {
            return m_isActive;
        }
    private:
        CameraTargetPriority m_priority;
        bool m_isActive = true;
    };
}
