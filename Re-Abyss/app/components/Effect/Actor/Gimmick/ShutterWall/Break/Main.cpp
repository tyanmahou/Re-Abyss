#include <abyss/components/Effect/Actor/Gimmick/ShutterWall/Break/Main.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterUtil.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>

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
        m_velocity.x = s3d::Random(-240, 240);
        m_velocity.y = s3d::Random(-400, -800);
    }
    void PieceParts::update(double dt)
    {
        m_localPos += m_velocity * dt;
        auto accelX = -s3d::Sign(m_velocity.x) * 360.0 * dt;
        if (m_velocity.x > 0 && m_velocity.x + accelX <= 0) {
            m_velocity.x = 0;
        } else if (m_velocity.x < 0 && m_velocity.x + accelX >= 0) {
            m_velocity.x = 0;
        } else {
            m_velocity.x += accelX;
        }

        m_velocity.y += 720.0 * dt;
        if (m_velocity.y >= 100) {
            m_velocity.y = 100;
        }
    }
    void PieceParts::draw(const s3d::ColorF& color) const
    {
        m_tri.movedBy(m_localPos).draw(color);
    }
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_pos(pos),
        m_timer(2.0)
    {
        {
            auto rect = ShutterUtil::RegionFromCenter(m_pos);
            auto pivot = s3d::RandomVec2(rect);

            m_pieces << PieceParts{ rect.tl(), rect.tr(), pivot };
            m_pieces << PieceParts{ rect.tr(), rect.br(), pivot };
            m_pieces << PieceParts{ rect.tl(), rect.bl(), pivot };
            m_pieces << PieceParts{ rect.bl(), rect.br(), pivot };
        }
    }
    void Main::onUpdate()
    {
        auto dt = m_pObj->deltaTime();
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
