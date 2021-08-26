#include "TimeScaleCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/params/Actor/Gimmick/Bush/Param.hpp>
#include <abyss/components/Actor/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <Siv3D.hpp>
namespace abyss::Actor::Gimmick::Bush
{
    TimeScaleCtrl::TimeScaleCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void TimeScaleCtrl::onStart()
    {
        m_cols = m_pActor->find<CollisionCtrl>();
    }
    void TimeScaleCtrl::onPostCollision()
    {
        auto callback = [this](const Body& data) {
            double speed = s3d::Abs(data.getVelocity().x);
            if (speed >= 10.0) {
                m_scale = s3d::Math::Lerp(1.0, Param::HitTimeScale, s3d::Saturate((speed - 10) / 60.0));
                return true;
            }
            return false;
        };
        m_isCollided = m_cols->anyThen<Tag::Player, Body>(callback)
            || m_cols->anyThen<Tag::Enemy, Body>(callback);
    }
    double TimeScaleCtrl::timeScale()
    {
        return m_isCollided ? m_scale: 1.0;
    }
}
