#pragma once
#include <memory>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Array.hpp>
#include <abyss/modules/Camera/CameraFix/base/ICameraFix.hpp>

namespace abyss
{
    class CameraFixCtrl
    {
    public:
        s3d::Vec2 apply(const s3d::Vec2& targetPos) const;

        void add(const std::shared_ptr<ICameraFix>& fix);
        void remove(const std::shared_ptr<ICameraFix>& fix);
    private:
        s3d::Array<std::shared_ptr<ICameraFix>> m_fixs;
    };
}
