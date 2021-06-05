#include "CameraTarget.hpp"
#include <abyss/modules/Camera/CameraTarget/base/ICameraTarget.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <Siv3D.hpp>

namespace  abyss
{
    CameraTarget::CameraTarget():
        m_lerpTimer(0.5s, false, [this] {return Clock::FromSec(m_time); })
    {
        m_lerpTimer.set(0s);
    }

    void CameraTarget::add(const std::shared_ptr<ICameraTarget>& target)
    {
        m_targets.push_back(target);
    }
    const s3d::Vec2& CameraTarget::update(double dt)
    {
        m_time += dt;

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

        // 変わっていたら補間する
        if (m_current != current) {
            m_prev = m_current;
            m_current = current;
            m_time = 0;
            m_lerpTimer.restart(0.5s);
        }

        // ターゲット座標更新
        if (m_current) {
            if (m_lerpTimer.reachedZero() || !m_prev) {
                m_targetPos = m_current->targetPos();
            } else {
                m_targetPos = s3d::Math::Lerp(m_prev->targetPos(), m_current->targetPos(), m_lerpTimer.progress0_1());
            }
        }
        return m_targetPos;
    }
}
