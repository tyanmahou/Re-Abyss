#include <abyss/components/Effect/Actor/Gimmick/ShutterWall/Break/Main.hpp>

namespace abyss::Effect::Actor::Gimmick::ShutterWall::Break
{
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos):
        m_pObj(pObj),
        m_pos(pos)
    {}
    void Main::onUpdate()
    {

    }
    bool Main::onDraw(double time)
    {
        return time <= 1.0;
    }
}
