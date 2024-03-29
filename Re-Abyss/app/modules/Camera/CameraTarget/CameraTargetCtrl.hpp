#pragma once
#include <memory>
#include <abyss/utils/Ref/Ref.hpp>
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
        const s3d::Vec2& update();
        const s3d::Vec2& targetPos() const
        {
            return m_targetPos;
        }
        double zoomScale() const
        {
            return m_zoomScale;
        }
    private:
        s3d::Array<Ref<ICameraTarget>> m_targets;
        s3d::Vec2 m_targetPos;
        double m_zoomScale = 1.0;
    };
}
