#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/BaseState.hpp>
#include <abyss/modules/Camera/Quake/QuakeEpicenter.hpp>
#include <abyss/modules/Camera/CameraTarget/base/CameraTargetBase.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class CameraTarget final : public CameraTargetBase
    {
    public:
        CameraTarget(const s3d::Vec2& pos) :
            CameraTargetBase(CameraTargetPriority::BossAction),
            m_pos(pos)
        {

        }
    public:
        s3d::Vec2 targetPos() const override
        {
            return m_pos;
        }
        double zoomScale() const override
        {
            return m_zoomScale;
        }
        void update(double dt)
        {
            m_timer.update(dt);
            m_zoomScale = s3d::Math::Lerp(1.0, 1.05, m_timer.rate());
        }
    private:
        s3d::Vec2 m_pos;
        double m_zoomScale = 1;
        TimeLite::Timer m_timer{ ShotParam::Wait::ScaleTime };
    };

    class WaitState final: public BaseState
    {
    public:
        void start()override;
        void end()override;
        Fiber<> task() override;
        void update() override;
    private:
        Ref<QuakeEpicenter> m_quake;
        std::shared_ptr<CameraTarget> m_cameraTarget;
    };
}
