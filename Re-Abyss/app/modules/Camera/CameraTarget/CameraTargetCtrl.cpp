#include <abyss/modules/Camera/CameraTarget/CameraTargetCtrl.hpp>

#include <abyss/commons/Constants.hpp>
#include <abyss/modules/Camera/CameraTarget/base/ICameraTarget.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <Siv3D.hpp>

namespace  abyss
{
    CameraTargetCtrl::CameraTargetCtrl() :
        m_targetPos(Constants::GameScreen.center())
    {
    }

    void CameraTargetCtrl::add(const std::shared_ptr<ICameraTarget>& target)
    {
        m_targets.push_back(target);
    }
    const s3d::Vec2& CameraTargetCtrl::update(double dt)
    {
        // 不要なもの削除
        m_targets.remove_if([](const Ref<ICameraTarget>& elm) {
            return !elm;
        });

        // 現在のターゲット候補選出
        std::shared_ptr<ICameraTarget> current = nullptr;
        for (const auto& target : m_targets) {
            if (!target->isActive()) {
                continue;
            }
            if (!current || current->priority() <= target->priority()) {
                current = target.lock();
            }
        }
        // ターゲット座標更新
        if (current) {
            m_targetPos = current->targetPos();
            m_zoomScale = current->zoomScale();
        }
        return m_targetPos;
    }
}
