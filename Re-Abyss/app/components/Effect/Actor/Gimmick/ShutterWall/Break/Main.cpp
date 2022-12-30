#include <abyss/components/Effect/Actor/Gimmick/ShutterWall/Break/Main.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterUtil.hpp>

namespace abyss::Effect::Actor::Gimmick::ShutterWall::Break
{
    using namespace abyss::Actor::Gimmick::ShutterWall;

    PieceParts::PieceParts(const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2):
        m_tri{p0, p1, p2}
    {
    }
    PieceParts::PieceParts(const s3d::Triangle& tri):
        m_tri(tri)
    {
    }
    void PieceParts::update(double dt)
    {
    }
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_pos(pos)
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

    }
    bool Main::onDraw(double time)
    {
        return time <= 1.0;
    }
}
