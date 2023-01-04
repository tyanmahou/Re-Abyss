#include <abyss/components/Effect/Actor/Gimmick/ShutterWall/Break/Main.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterUtil.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/params/Actor/Gimmick/ShutterWall/Param.hpp>
#include <abyss/params/Actor/Gimmick/ShutterWall/EffectParam.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Effect::Actor::Gimmick::ShutterWall::Break
{
    using namespace abyss::Actor::Gimmick::ShutterWall;

    PieceParts::PieceParts(const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const s3d::Vec2& center):
        PieceParts(Triangle{p0, p1, p2}, center)
    {
    }
    PieceParts::PieceParts(const s3d::Triangle& polygon, const s3d::Vec2& center):
        m_polygon(polygon),
        m_localPos(0, 0),
        m_center(center)
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
        const auto movedPoly = m_polygon.movedBy(m_localPos);
        const auto resultPoly = movedPoly.rotatedAt(movedPoly.centroid(), s3d::ToRadians(m_rotate));
        {
            Buffer2D buff{3, 1};
            auto toVertex = [&](size_t index) ->Vertex2D{
                return {
                    .pos = resultPoly.p(index),
                    .tex = (m_polygon.p(index) - (m_center - Param::BaseSize / 2)) / Param::BaseSize,
                    .color = color.toFloat4()
                };
            };
            buff.vertices[0] = toVertex(0);
            buff.vertices[1] = toVertex(1);
            buff.vertices[2] = toVertex(2);
            buff.indices[0] = TriangleIndex{0, 1, 2};
            buff.draw(Resource::Assets::Main()->loadTexturePacker(U"Actor/Gimmick/ShutterWall/ShutterWall.json")(U"wall"));
        }
    }
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_pos(pos),
        m_timer(EffectParam::LifeTime)
    {
        {
            auto rect = ShutterUtil::RegionScaledFromCenter(m_pos, 0.5);
            auto pivot = s3d::RandomVec2(rect);

            m_pieces << PieceParts{ rect.tl(), rect.tr(), pivot, m_pos };
            m_pieces << PieceParts{ rect.tr(), rect.br(), pivot, m_pos };
            m_pieces << PieceParts{ rect.tl(), rect.bl(), pivot, m_pos };
            m_pieces << PieceParts{ rect.bl(), rect.br(), pivot, m_pos };
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
