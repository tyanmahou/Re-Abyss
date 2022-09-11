#include <abyss/components/Actor/Player/CameraTarget.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <abyss/utils/Math/Math.hpp>

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
        void onPostPhysics()
        {
            auto dt = m_pActor->deltaTime();
            Vec2 velocity{ 0,0 };
            if (!Math::IsZeroLoose(dt)) {
                // 地形衝突を考慮するためにvelocityは直接使わない
                velocity = m_body->moveDiff() / dt;
            }
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
            } else {
                targetLocalPos.x = m_localPos.x;
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
            } else {
                targetLocalPos.y = m_localPos.y;
            }
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
        executer.onStart().addAfter<Body>();
        executer.on<IPostPhysics>().addAfter<MapCollider>();
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
    void CameraTarget::onPostPhysics()
    {
        m_target->onPostPhysics();
    }
}
