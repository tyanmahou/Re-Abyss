#include <abyss/components/Actor/Enemy/BazookaKun/State/WaitState.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/State/AimState.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    void WaitState::start()
    {
    }
    void WaitState::update()
    {
        const auto& pos = m_body->getPos();
        // 基準点の計算
        RectF rect{ pos - Vec2{45, 30}, Vec2{90, 60} };
        auto center = rect.center();
        auto pivot = center + Vec2{ m_target->isMirrored() ? 3 : -3, m_target->isFlipped() ? -15 : 15};
        pivot = pivot.rotateAt(rect.bl(), s3d::ToRadians(m_target->rotate()));

        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);

        auto eyeVec = Vec2{ m_target->isMirrored() ? 1 : -1, 0 }.rotated(s3d::ToRadians(m_target->rotate()));

        auto toPlayer = playerPos - pivot;
        Vec2 toPlayerUnit{ 0,0 };
        if (!toPlayer.isZero()) {
            toPlayerUnit = toPlayer.normalized();
        }
        // ある程度近く前方なら遷移
        constexpr double dist = 500;
        if (
            toPlayer.lengthSq() <= (dist * dist) &&
            toPlayerUnit.dot(eyeVec) > Cos(s3d::ToRadians(90))
        ) {
            this->changeState<AimState>();
        }
    }
    Task<> WaitState::task()
    {
        co_return;
    }
}
