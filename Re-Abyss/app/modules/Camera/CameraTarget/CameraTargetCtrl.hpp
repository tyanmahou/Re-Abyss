#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss
{
    class ICameraTarget;

    class CameraTargetCtrl
    {
    public:
        CameraTargetCtrl();

        void add(const std::shared_ptr<ICameraTarget>& target);
        const s3d::Vec2& update(double dt);
        const s3d::Vec2& targetPos() const
        {
            return m_targetPos;
        }
    private:
        s3d::Array<std::shared_ptr<ICameraTarget>> m_targets;
        s3d::Vec2 m_targetPos{0, 0};
    };
}