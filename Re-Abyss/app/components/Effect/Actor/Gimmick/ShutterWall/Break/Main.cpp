#include <abyss/components/Effect/Actor/Gimmick/ShutterWall/Break/Main.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterUtil.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/params/Actor/Gimmick/ShutterWall/EffectParam.hpp>

namespace abyss::Effect::Actor::Gimmick::ShutterWall::Break
{
    using namespace abyss::Actor::Gimmick::ShutterWall;

    PieceParts::PieceParts(const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2):
        PieceParts(Triangle{p0, p1, p2})
    {
    }
    PieceParts::PieceParts(const s3d::Triangle& tri):
        m_tri(tri),
        m_localPos(0, 0)
    {
        const double angle = s3d::Random(-EffectParam::InitVelocityAngleRange, EffectParam::InitVelocityAngleRange);
        m_velocity = s3d::Circular0{
            s3d::Random(EffectParam::InitSpeedMin, EffectParam::InitSpeedMax),
            s3d::ToRadians(angle)
        }.fastToVec2();

        // 左右にふっとびすぎないように水平方向速度だけ補正をかける
        const double angleRate = s3d::Abs(angle) / EffectParam::InitVelocityAngleRange;
        double speedHFactor = s3d::Math::Lerp(1.0, 0.7, angleRate);
        m_velocity.x *= speedHFactor;
    }
    void PieceParts::update(double dt)
    {
        m_localPos += m_velocity * dt;
        auto accelX = -s3d::Sign(m_velocity.x) * EffectParam::DecelH * dt;
        if (m_velocity.x > 0 && m_velocity.x + accelX <= 0) {
            m_velocity.x = 0;
        } else if (m_velocity.x < 0 && m_velocity.x + accelX >= 0) {
            m_velocity.x = 0;
        } else {
            m_velocity.x += accelX;
        }

        m_velocity.y += EffectParam::Gravity * dt;
        if (m_velocity.y >= EffectParam::MaxSpeedV) {
            m_velocity.y = EffectParam::MaxSpeedV;
        }

        // 回転
        m_rotateSpeed = s3d::Clamp(m_velocity.length() * 0.7, 0.0, 360.0);
        m_rotate += s3d::Sign(m_velocity.x) * m_rotateSpeed * dt;
    }
    void PieceParts::draw(const s3d::ColorF& color) const
    {
        const auto movedTri = m_tri.movedBy(m_localPos);
        movedTri.rotatedAt(movedTri.centroid(), s3d::ToRadians(m_rotate))
            .draw(color);
    }
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_pos(pos),
        m_timer(EffectParam::LifeTime)
    {
        {
            auto rect = ShutterUtil::RegionScaledFromCenter(m_pos, 0.5);
            auto pivot = s3d::RandomVec2(rect);

            m_pieces << PieceParts{ rect.tl(), rect.tr(), pivot };
            m_pieces << PieceParts{ rect.tr(), rect.br(), pivot };
            m_pieces << PieceParts{ rect.tl(), rect.bl(), pivot };
            m_pieces << PieceParts{ rect.bl(), rect.br(), pivot };
        }
    }
    void Main::onUpdate()
    {
        auto dt = m_pObj->deltaTime() * EffectParam::TimeScale;
        m_timer.update(dt);
        for (auto&& p : m_pieces) {
            p.update(dt);
        }
    }
    bool Main::onDraw([[maybe_unused]]double time)
    {
        for (auto&& p : m_pieces) {
            p.draw(ColorF(1, m_timer.invRate()));
        }
        return !m_timer.isEnd();
    }
}
