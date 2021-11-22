#include "ColReactor.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/params/Actor/Gimmick/Bush/Param.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Gimmick::Bush
{
    ColReactor::ColReactor(ActorObj* pActor):
        m_pActor(pActor),
        m_timeScale(Param::BaseTimeScale)
    {}
    void ColReactor::onStart()
    {
        m_cols = m_pActor->find<ColCtrl>();
    }
    void ColReactor::onPostCollision()
    {
        m_resizeRate = 0.0;
        m_timeScale = Param::BaseTimeScale;

        m_cols->eachThen<Col::Attacker>([&](const Col::Attacker::Data& attacker) {
            Vec2 speed = s3d::Math::Abs(attacker.velocity);
            if (auto s = s3d::Max(speed.x, speed.y); s >= 10) {
                m_resizeRate = s3d::Max(m_resizeRate, s3d::Saturate((s - 10) / 60.0));
            }
            if (speed.x >= 10.0) {
                m_timeScale = s3d::Max(m_timeScale, s3d::Math::Lerp(
                    Param::BaseTimeScale,
                    Param::HitTimeScale,
                    s3d::Saturate((speed.x - 10) / Param::MaxTimeScaleSpeed)
                ));
            }
            return true;
        });
    }
    double ColReactor::getResizeRate() const
    {
        return m_resizeRate;
    }
    double ColReactor::timeScale()
    {
        return m_timeScale;
    }
}
