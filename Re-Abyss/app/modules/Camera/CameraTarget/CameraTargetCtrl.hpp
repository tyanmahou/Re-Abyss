#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <Siv3D/Vector2D.hpp>

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
        double zoomScale() const
        {
            return m_zoomScale;
        }
    private:
        s3d::Array<std::shared_ptr<ICameraTarget>> m_targets;
        s3d::Vec2 m_targetPos;
        double m_zoomScale = 1.0;

        s3d::Vec2 m_targetPosBuffer;
        double m_zoomScaleBuffer = 1.0;
    };
}
