#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss
{
    class ICameraTarget;

    class CameraTarget
    {
    public:
        CameraTarget();

        void add(const std::shared_ptr<ICameraTarget>& target);
        const s3d::Vec2& update(double dt);
    private:
        s3d::Array<std::shared_ptr<ICameraTarget>> m_targets;

        std::shared_ptr<ICameraTarget> m_current;
        std::shared_ptr<ICameraTarget> m_prev;

        TimerEx m_lerpTimer;
        double m_time = 0;

        s3d::Vec2 m_targetPos;
    };
}