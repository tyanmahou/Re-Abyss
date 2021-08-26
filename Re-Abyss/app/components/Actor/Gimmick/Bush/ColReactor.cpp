#include "ColReactor.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/params/Actor/Gimmick/Bush/Param.hpp>
#include <abyss/components/Actor/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Gimmick::Bush
{
    ColReactor::ColReactor(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void ColReactor::onStart()
    {
        m_cols = m_pActor->find<CollisionCtrl>();
    }
    void ColReactor::onPostCollision()
    {
        m_resizeRate = 0.0;
        m_timeScale = 1.0;

        for (auto* pHitActor : m_cols->getHitActors()) {
            if (!pHitActor->getTag().anyOf<Tag::Enemy, Tag::Player>()) {
                continue;
            }
            auto body = pHitActor->find<Body>();
            if (!body) {
                continue;
            }

            Vec2 speed = s3d::Abs(body->getVelocity());
            if (auto s = s3d::Max(speed.x, speed.y); s >= 10) {
                m_resizeRate = s3d::Max(m_resizeRate, s3d::Saturate((s - 10) / 60.0));
            }
            if (speed.x >= 10.0) {
                m_timeScale = s3d::Max(m_timeScale, s3d::Math::Lerp(1.0, Param::HitTimeScale, s3d::Saturate((speed.x - 10) / 60.0)));
            }
        }
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
