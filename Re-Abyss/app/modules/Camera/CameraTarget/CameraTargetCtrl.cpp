#include "CameraTargetCtrl.hpp"
#include <abyss/modules/Camera/CameraTarget/base/ICameraTarget.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <Siv3D.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
namespace  abyss
{
    CameraTargetCtrl::CameraTargetCtrl()
    {
    }

    void CameraTargetCtrl::add(const std::shared_ptr<ICameraTarget>& target)
    {
        m_targets.push_back(target);
    }
    const s3d::Vec2& CameraTargetCtrl::update(double dt)
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
            auto interpRate = current->interpRate();
            if (interpRate >= 1.0) {
                m_targetPos = current->targetPos();
            } else if(interpRate <= 0.0){
                // 更新なし
                // m_targetPos = m_targetPos
            } else {
                m_targetPos = s3d::Math::Lerp(m_targetPos, current->targetPos(), InterpUtil::DampRatio(current->interpRate(), dt));
            }
        }
        return m_targetPos;
    }
}
