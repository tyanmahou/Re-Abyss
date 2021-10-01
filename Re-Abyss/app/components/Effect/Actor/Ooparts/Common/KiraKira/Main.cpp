#include "Main.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Ooparts::KiraKira
{
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos, Type type):
        m_pObj(pObj),
        m_view(type)
    {
        m_view.setPos(pos);
    }
    bool Main::onDraw(double time)
    {
        m_view.setTime(time).draw();
        return time <= 1.0;
    }
}