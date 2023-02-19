#include <abyss/components/Effect/Actor/Enemy/CodeZero/NegaPosi/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::NegaPosi
{
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos):
        m_pObj(pObj),
        m_pos(pos)
    {}
    void Main::onStart()
    {
        m_pObj->getModule<PostEffects>()->getNegaPosiInv()->setIsValid(true);
    }
    void Main::onEnd()
    {
        m_pObj->getModule<PostEffects>()->getNegaPosiInv()->setIsValid(false);
    }
    bool Main::onDraw(double time)
    {
        double rate = s3d::EaseOutCirc(time / 0.5);
        m_pObj->getModule<PostEffects>()->getNegaPosiInv()->maskRecord([&] {
            Circle(m_pos, 700 * rate).draw(ColorF(1, rate));
        });
        return time <= 0.5;
    }
}
