#include <abyss/modules/Camera/CameraTarget/CameraTargetCtrl.hpp>

#include <abyss/commons/Constants.hpp>
#include <abyss/modules/Camera/CameraTarget/base/ICameraTarget.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
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
            auto interpRate = current->interpRate();
            if (interpRate >= 1.0) {
                m_targetPos = current->targetPos();
                m_zoomScale = current->zoomScale();
            } else if(interpRate <= 0.0){
                // 更新なし
                // m_targetPos = m_targetPos
                // m_zoomScale = m_zoomScale
            } else {
                double damp = InterpUtil::DampRatio(current->interpRate(), dt, 120_fps);
                m_targetPos = s3d::Math::Lerp(m_targetPos, current->targetPos(), damp);
                m_zoomScale = s3d::Math::Lerp(m_zoomScale, current->zoomScale(), damp);
            }
        }
        return m_targetPos;
    }
}
