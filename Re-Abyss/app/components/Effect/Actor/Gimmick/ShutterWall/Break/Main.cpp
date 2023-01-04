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

    s3d::Array<Vertex2D> PieceParts::vertices(const s3d::ColorF& color) const
    {
        const auto movedPoly = m_polygon.movedBy(m_localPos);
        const auto resultPoly = movedPoly.rotatedAt(movedPoly.centroid(), s3d::ToRadians(m_rotate));

        auto toVertex = [&](size_t index) ->Vertex2D {
            return {
                .pos = resultPoly.p(index),
                .tex = (m_polygon.p(index) - (m_center - Param::BaseSize / 2)) / Param::BaseSize,
                .color = color.toFloat4()
            };
        };
        return {
            toVertex(0),
            toVertex(1),
            toVertex(2),
        };
    }
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_pos(pos),
        m_timer(EffectParam::LifeTime)
    {
        // ポリゴンの分割
        // 四角形を複数の三角形に分ける
        {
            const auto rect = ShutterUtil::RegionFromCenter(m_pos);
            const auto pivot = s3d::RandomVec2(rect.scaledAt(m_pos, 0.5));

            auto addPieces = [&](size_t i0, size_t i1, bool isRecursive){
                const auto p0 = rect.point(i0);
                const auto p1 = rect.point(i1);

                if (isRecursive) {
                    // 再帰分割
                    const Triangle tri{ p0, p1, pivot };
                    const auto pivot2 = s3d::RandomVec2(tri.scaledAt(tri.centroid(), 0.5));

                    m_pieces << PieceParts{ p0, p1, pivot2, m_pos };
                    m_pieces << PieceParts{ p0, pivot2, pivot, m_pos };
                    m_pieces << PieceParts{ pivot2, p1, pivot, m_pos };
                } else {
                    m_pieces << PieceParts{ p0, p1, pivot, m_pos };
                }
            };

            auto recursiveFlag = s3d::Random(0, 15);
            addPieces(0, 1, (recursiveFlag & 0x01) != 0);
            addPieces(1, 2, (recursiveFlag & 0x02) != 0);
            addPieces(2, 3, (recursiveFlag & 0x04) != 0);
            addPieces(3, 0, (recursiveFlag & 0x08) != 0);
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
        const auto color = ColorF(1, m_timer.invRate());
        Buffer2D buff;
        buff.vertices.reserve(m_pieces.size() * 3);
        buff.indices.reserve(m_pieces.size());

        for (const auto& [index, p] : s3d::Indexed(m_pieces)) {
            for (const auto& v : p.vertices(color)) {
                buff.vertices << v;
            }
            buff.indices << TriangleIndex{
                static_cast<TriangleIndex::value_type>(3 * index + 0),
                static_cast<TriangleIndex::value_type>(3 * index + 1),
                static_cast<TriangleIndex::value_type>(3 * index + 2)
            };
        }
        buff.draw(Resource::Assets::Main()->loadTexturePacker(U"Actor/Gimmick/ShutterWall/ShutterWall.json")(U"wall"));
        return !m_timer.isEnd();
    }
}
