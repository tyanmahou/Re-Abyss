#include <abyss/components/Effect/Actor/Common/Breath/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Breath
{
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_pos(pos)
    {
    }

    Main::~Main()
    {}

    bool Main::onDraw(double time)
    {
        ScopedRenderStates2D blend(BlendState::Additive);

        auto pos = m_pos + Vec2{ 10 * Sin(time * 1.5), -60 * time };
        Circle(pos, 3).drawFrame(0.5, ColorF(0.5));
        return time < 10.0;
    }
}
