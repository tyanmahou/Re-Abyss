#include "CameraTarget.hpp"
#include <abyss/modules/Camera/CameraTarget/base/ICameraTarget.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <Siv3D.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
namespace  abyss
{
    CameraTarget::CameraTarget()
    {
    }

    void CameraTarget::add(const std::shared_ptr<ICameraTarget>& target)
    {
        m_targets.push_back(target);
    }
    const s3d::Vec2& CameraTarget::update(double dt)
    {
        // 不要なもの削除
        m_targets.remove_if([](const std::shared_ptr<ICameraTarget>& elm) {
            return elm->isEnd();
        });

        // 現在のターゲット候補選出
        std::shared_ptr<ICameraTarget> current = nullptr;
        for (const auto& target : m_targets) {
            if (!target->isActive()) {
                continue;
            }
            if (!current || current->priority() <= target->priority()) {
                current = target;
            }
        }
        // ターゲット座標更新
        if (current) {
            auto targetPosPrev = m_targetPos;
            m_targetPos = s3d::Math::Lerp(targetPosPrev, current->targetPos(), InterpUtil::DampRatio(0.05, dt));
        }
        return m_targetPos;
    }
}
