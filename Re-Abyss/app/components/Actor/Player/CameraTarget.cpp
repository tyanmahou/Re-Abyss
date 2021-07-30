#include "CameraTarget.hpp"

#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/BodyUpdater.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>

#include <abyss/params/Actor/Player/Param.hpp>
#include <abyss/params/Actor/Player/CameraParam.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    class CameraTarget::Impl : public CameraTargetBase
    {
    public:
        Impl(ActorObj* pActor) :
            CameraTargetBase(CameraTargetPriority::Player),
            m_pActor(pActor)
        {}
        s3d::Vec2 targetPos() const
        {
            return m_body->getCenterPos() + m_localPos;
        }

        void onStart()
        {
            m_body = m_pActor->find<Body>();
        }
        void onMove()
        {
            const auto& velocity = m_body->getVelocity();
            s3d::Vec2 targetLocalPos{0, 0};
            const auto& maxOffset = CameraParam::MaxOffsetPos;
            const auto& startSpeed = CameraParam::StartSpeed;
 
            if (velocity.x > startSpeed.x) {
                targetLocalPos.x = s3d::Math::Lerp(
                    0,
                    maxOffset.x,
                    s3d::Saturate((velocity.x - startSpeed.x) / (Param::Swim::MaxSpeedX - startSpeed.x))
                );
            } else if (velocity.x < -startSpeed.x) {
                targetLocalPos.x = s3d::Math::Lerp(
                    0,
                    -maxOffset.x,
                    s3d::Saturate((-velocity.x - startSpeed.x) / (Param::Swim::MaxSpeedX - startSpeed.x))
                );
            }

            if (velocity.y > startSpeed.y) {
                targetLocalPos.y = s3d::Math::Lerp(
                    0,
                    maxOffset.y,
                    s3d::Saturate((velocity.y - startSpeed.y) / (Param::Swim::DiveSpeed - startSpeed.y))
                );
            } else if (velocity.y < -startSpeed.y) {
                targetLocalPos.y = s3d::Math::Lerp(
                    0,
                    -maxOffset.y,
                    s3d::Saturate((-velocity.y - startSpeed.y) / (Param::Swim::MaxSpeedX - startSpeed.y))
                );
            }

            auto dt = m_pActor->deltaTime();
            m_localPos = s3d::Math::Lerp(m_localPos, targetLocalPos, InterpUtil::DampRatio(CameraParam::ErpRate, dt));
        }
    private:
        ActorObj* m_pActor;

        s3d::Vec2 m_localPos{0, 0};
        Ref<Body> m_body;
    };
    CameraTarget::CameraTarget(ActorObj* pActor) :
        m_pActor(pActor),
        m_target(std::make_shared<Impl>(pActor))
    {}
    void CameraTarget::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<Body>();
        executer.on<IMove>().addAfter<BodyUpdater>();
    }
    void CameraTarget::onStart()
    {
        m_pActor->getModule<Camera>()->addTarget(m_target);
        m_target->onStart();
    }
    void CameraTarget::onEnd()
    {
        m_target->destory();
    }
    void CameraTarget::onMove()
    {
        m_target->onMove();
    }
}
