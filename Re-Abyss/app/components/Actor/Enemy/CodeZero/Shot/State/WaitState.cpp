#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/WaitState.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/PursuitState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/ShotProxy.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Camera/CameraTarget/base/CameraTargetBase.hpp>
#include <abyss/components/Effect/Actor/Enemy/CodeZero/ShotCharge/Builder.hpp>
#include <abyss/components/Effect/Actor/Enemy/CodeZero/NegaPosi/Builder.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    using namespace Effect::Actor::Enemy::CodeZero;

    class WaitState::CameraTarget final : public CameraTargetBase
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
    public:
        void zoom()
        {
            m_timer.reset(ShotParam::Wait::ScaleTime);
            m_isZoom = true;
        }
        void unzoom()
        {
            m_timer.reset(0.5);
            m_isZoom = false;
        }
        void update(double dt)
        {
            m_timer.update(dt);
            if (m_isZoom) {
                m_zoomScale = s3d::Math::Lerp(1.0, 1.05, s3d::EaseOutCirc(m_timer.rate()));
            } else {
                m_zoomScale = s3d::Math::Lerp(1.05, 1.0, s3d::EaseOutCirc(m_timer.rate()));
            }
        }
    private:
        s3d::Vec2 m_pos;
        double m_zoomScale = 1;
        bool m_isZoom = true;
        TimeLite::Timer m_timer{ };
    };
    void WaitState::start()
    {
        m_effects << m_pActor
            ->getModule<Effects>()
            ->createWorldFront<ShotCharge::Builder>(m_body->getPos());

        m_quake = m_pActor
            ->getModule<Camera>()
            ->startQuake(1.0);
    }

    void WaitState::end()
    {
        if (m_quake) {
            m_quake->stop();
        }
        for (auto&& effect : m_effects) {
            if (effect) {
                effect->destroy();
            }
        }
    }
    Fiber<> WaitState::task()
    {
        auto shot = m_pActor->find<ShotProxy>();

        // カメラズーム
        m_cameraTarget = std::make_shared<CameraTarget>(m_body->getPos());
        m_cameraTarget->zoom();
        m_pActor->getModule<Camera>()->addTarget(m_cameraTarget);

        // きゅ～～ん
        shot->setIsCharge(true);
        m_scale->setTo(0.2, ShotParam::Wait::ScaleTime);
        co_await BehaviorUtil::WaitForSeconds(m_pActor, ShotParam::Wait::ScaleTime + 0.2);

        // しゅっ
        m_scale->setTo(0, 0.3);
        shot->setIsCharge(false);
        if (m_quake) {
            m_quake->stop();
        }

        // ちょっとまってから
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 1);

        // どん！
        m_scale->setTo(1.0, 0.1);
        m_pActor->getModule<Camera>()->startQuake(5.0, 0.1);
        // ズーム解除
        m_cameraTarget->unzoom();

        // ネガポジエフェクト
        m_effects << m_pActor
            ->getModule<Effects>()
            ->createWorldFront<NegaPosi::Builder>(m_body->getPos());

        // ちょっとまってから
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.5);

        // 追従開始
        this->changeState<PursuitState>();
    }
    void WaitState::update()
    {
        auto dt = m_pActor->deltaTime();
        m_scale->update(dt);

        if (m_cameraTarget) {
            m_cameraTarget->update(dt);
        }
    }
}

